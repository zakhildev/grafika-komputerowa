#include "../include/Model.hpp"
#include "../include/stb_image.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;
using namespace Assimp;

Model::Model(string const &path, bool gamma) : gammaCorrection(gamma) {
  this->dir = path.substr(0, path.find_last_of('/'));
  loadModel(path);
}

void Model::Draw(Shader &shader) {
  for (uint i = 0; i < meshes.size(); i++) {
    meshes[i].Draw(shader);
  }
}

void Model::loadModel(const string &path) {
  Importer importer;
  std::cout << "[Model] Loading: " << path << std::endl;
  const aiScene *scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cerr << "[Error] Assimp failed to load: " << importer.GetErrorString()
              << std::endl;
    return;
  }

  std::cout << "[Model] Model loaded successfully. Meshes: "
            << scene->mNumMeshes << std::endl;
  processNode(scene->mRootNode, scene);
  std::cout << "[Model] Total meshes processed: " << meshes.size() << std::endl;
}

void Model::processNode(aiNode *node, const aiScene *scene) {
  for (uint i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }

  for (uint i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  vector<Vertex> vertices;
  vector<uint> indices;
  vector<Texture> textures;

  for (uint i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;

    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
    }

    if (mesh->HasTextureCoords(0)) {
      vec2 textureCoord;
      textureCoord.x = mesh->mTextureCoords[0][i].x;
      textureCoord.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoords = textureCoord;

      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.Tangent = vector;

      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.Bitangent = vector;
    } else {
      vertex.TexCoords = vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  for (uint i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (uint j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
  std::cout << "[Mesh] Processing mesh with material index: "
            << mesh->mMaterialIndex << std::endl;

  // Extract material properties
  Material meshMaterial{vec3(1.0f), vec3(1.0f), 32.0f, 0.0f, 1.0f};

  aiColor3D diffuseColor(1.0f, 1.0f, 1.0f);
  if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS) {
    meshMaterial.diffuse = vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);
    std::cout << "[Material] Diffuse color: (" << meshMaterial.diffuse.r << ", "
              << meshMaterial.diffuse.g << ", " << meshMaterial.diffuse.b << ")"
              << std::endl;
  }

  aiColor3D specularColor(1.0f, 1.0f, 1.0f);
  if (material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS) {
    meshMaterial.specular =
        vec3(specularColor.r, specularColor.g, specularColor.b);
    std::cout << "[Material] Specular color: (" << meshMaterial.specular.r
              << ", " << meshMaterial.specular.g << ", "
              << meshMaterial.specular.b << ")" << std::endl;
  }

  float shininess = 32.0f;
  if (material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
    meshMaterial.shininess = shininess;
    std::cout << "[Material] Shininess: " << meshMaterial.shininess
              << std::endl;
  }

  float metallic = 0.0f;
  if (material->Get(AI_MATKEY_METALLIC_FACTOR, metallic) == AI_SUCCESS) {
    meshMaterial.metallic = metallic;
    std::cout << "[Material] Metallic: " << meshMaterial.metallic << std::endl;
  } else {
    // Heuristic: High shininess suggests metallic material
    if (meshMaterial.shininess > 200.0f) {
      meshMaterial.metallic =
          std::min(1.0f, (meshMaterial.shininess - 200.0f) / 300.0f);
      std::cout << "[Material] Metallic (inferred): " << meshMaterial.metallic
                << std::endl;
    }
  }

  float alpha = 1.0f;
  if (material->Get(AI_MATKEY_OPACITY, alpha) == AI_SUCCESS) {
    meshMaterial.alpha = alpha;
    std::cout << "[Material] Alpha: " << meshMaterial.alpha << std::endl;
  }

  vector<Texture> diffuseMaps =
      loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
  vector<Texture> specularMaps = loadMaterialTextures(
      material, aiTextureType_SPECULAR, "texture_specular");
  vector<Texture> normalMaps =
      loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
  vector<Texture> heightMaps =
      loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");

  std::cout << "[Mesh] Diffuse: " << diffuseMaps.size()
            << ", Specular: " << specularMaps.size()
            << ", Normal: " << normalMaps.size()
            << ", Height: " << heightMaps.size() << std::endl;

  textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
  textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

  std::cout << "[Mesh] Total textures for mesh: " << textures.size()
            << std::endl;

  return Mesh(vertices, indices, textures, meshMaterial);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            string typeName) {
  vector<Texture> textures;
  uint count = mat->GetTextureCount(type);
  std::cout << "[Material] Type: " << typeName << ", Count: " << count
            << std::endl;

  for (uint i = 0; i < count; i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    bool skip = false;

    for (uint j = 0; j < textures_loaded.size(); j++) {
      if (textures_loaded[j].path == string(str.C_Str())) {
        std::cout << "[Material] Reusing cached texture: " << str.C_Str()
                  << std::endl;
        textures.push_back(textures_loaded[j]);
        skip = true;
        break;
      }
    }

    if (!skip) {
      Texture texture;
      std::cout << "[Material] Loading texture from " << str.C_Str() << " | "
                << this->dir << std::endl;
      texture.id = TextureFromFile(str.C_Str(), this->dir);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);
      textures_loaded.push_back(texture);
    }
  }

  return textures;
}

uint TextureFromFile(const char *path, const string &directory, bool gamma) {
  string filename = string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data =
      stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cerr << "[Error] Texture failed to load at path: " << path
              << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}