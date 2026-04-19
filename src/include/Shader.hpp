#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <sys/types.h>

using namespace std;
using namespace glm;

class Shader {
public:
  uint ID;

  Shader(const char *vertexPath, const char *fragmentPath);

  void use() const;

  void setBool(const string &name, bool value) const;
  void setInt(const string &name, int value) const;
  void setFloat(const string &name, float value) const;
  void setVec2(const string &name, const vec2 &value) const;
  void setVec2(const string &name, float x, float y) const;
  void setVec3(const string &name, const vec3 &value) const;
  void setVec3(const string &name, float x, float y, float z) const;
  void setVec4(const string &name, const vec4 &value) const;
  void setVec4(const string &name, float x, float y, float z, float w) const;
  void setMat2(const string &name, const mat2 &mat) const;
  void setMat3(const string &name, const mat3 &mat) const;
  void setMat4(const string &name, const mat4 &mat) const;
};
