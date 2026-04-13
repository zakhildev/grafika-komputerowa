#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <vector>

#include "Mesh.hpp"

using namespace std;
using namespace glm;
using namespace Assimp;

class Model {
public:
  vector<Mesh> meshes;
  void loadModel(const string &path);
  void Draw();

private:
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};
