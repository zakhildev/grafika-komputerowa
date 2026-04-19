#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;
using namespace Assimp;

uint TextureFromFile(const char *path, const string &directory,
                     bool gamma = false);

class Model {
public:
  vector<Texture> textures_loaded;
  vector<Mesh> meshes;
  string dir;
  bool gammaCorrection;

  Model(string const &path, bool gamma = false);

  void Draw(Shader &shader);

private:
  void loadModel(const string &path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                       string typeName);
};
