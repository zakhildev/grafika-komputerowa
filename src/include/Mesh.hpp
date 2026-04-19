#pragma once

#include "./Shader.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <sys/types.h>
#include <vector>

using namespace glm;
using namespace std;

typedef struct Vertex {
  vec3 Position;
  vec3 Normal;
  vec2 TexCoords;
  vec3 Tangent;
  vec3 Bitangent;
} Vertex;

typedef struct Texture {
  uint id;
  string type;
  string path;
} Texture;

typedef struct Material {
  vec3 diffuse;
  vec3 specular;
  float shininess;
  float metallic;
  float alpha;
} Material;

class Mesh {
public:
  vector<Vertex> vertices;
  vector<uint> indices;
  vector<Texture> textures;
  Material material;

  Mesh(vector<Vertex> vertices, vector<uint> indices, vector<Texture> textures,
       Material material = Material{vec3(1.0f), vec3(1.0f), 32.0f, 0.0f, 1.0f});
  void Draw(Shader &shader);

private:
  uint VAO, VBO, EBO;
  void setupMesh();
};
