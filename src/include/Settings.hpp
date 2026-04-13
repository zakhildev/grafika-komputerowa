#pragma once

#include <glm/glm.hpp>
#include <string>

class Settings {
public:
  float cameraSpeed = 0.05f;
  float mouseSensitivity = 0.005f;

  bool firstMouse = true;
  glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, -10.0f);
  float cameraYaw = 0.0f;
  float cameraPitch = 0.0f;
  bool keys[512] = {false};
  double lastMouseX = 0.0;
  double lastMouseY = 0.0;

  Settings();

  bool loadFromFile(const std::string &path = "settings.conf");
};

extern Settings settings;
