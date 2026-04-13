#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

typedef struct Vertex {
  vec3 Position;
  vec3 Normal;
  vec2 TexCoords;
  vec4 Color;
} Vertex;

class Mesh {
public:
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  unsigned int VAO, VBO, EBO;
  Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
  void Draw();

private:
  void setupMesh();
};
