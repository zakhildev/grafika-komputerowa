#include "../include/Model.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;
using namespace Assimp;

void Model::loadModel(const string &path) {
  Importer importer;
  const aiScene *scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_FlipUVs |
                aiProcess_CalcTangentSpace | aiProcess_PreTransformVertices);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    return;
  }

  processNode(scene->mRootNode, scene);
}

void Model::Draw() {
  for (unsigned int i = 0; i < meshes.size(); i++) {
    meshes[i].Draw();
  }
}

void Model::processNode(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  vector<Vertex> vertices;
  vector<unsigned int> indices;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    vertex.Position =
        vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
    vertex.Normal = mesh->HasNormals()
                        ? vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                               mesh->mNormals[i].z)
                        : vec3(0.0f, 0.0f, 0.0f);
    vertex.TexCoords = vec2(0.0f, 0.0f);
    vertex.Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if (mesh->mTextureCoords[0]) {
      vertex.TexCoords =
          vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
    }

    if (mesh->HasVertexColors(0)) {
      vertex.Color = vec4(mesh->mColors[0][i].r, mesh->mColors[0][i].g,
                          mesh->mColors[0][i].b, mesh->mColors[0][i].a);
    }

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  return Mesh(vertices, indices);
}
