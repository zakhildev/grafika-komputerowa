#pragma once

#include "./Shader.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace glm;
using namespace std;

class Skybox {
public:
  Skybox(vector<string> faces);
  void Draw(Shader &shader, mat4 P, mat4 V);

private:
  GLuint cubemapTexture;
  GLuint VAO, VBO;
  void setupSkybox();
  GLuint loadCubemap(vector<string> faces);
};
