#include "../include/Callbacks.hpp"
#include "../include/Settings.hpp"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

void Callbacks::error_callback(int error, const char *description) {
  fputs(description, stderr);
}

void Callbacks::key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods) {
  if (key >= 0 && key < 512) {
    if (action == GLFW_PRESS) {
      settings.keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      settings.keys[key] = false;
    }
  }
}

void Callbacks::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (settings.firstMouse) {
    settings.lastMouseX = xpos;
    settings.lastMouseY = ypos;
    settings.firstMouse = false;
    return;
  }

  double xoffset = xpos - settings.lastMouseX;
  double yoffset = settings.lastMouseY - ypos;

  settings.lastMouseX = xpos;
  settings.lastMouseY = ypos;

  settings.cameraYaw -= xoffset * settings.mouseSensitivity;
  settings.cameraPitch += yoffset * settings.mouseSensitivity;

  // Ograniczenie pitch'u
  if (settings.cameraPitch > M_PI / 2.0f - 0.1f)
    settings.cameraPitch = M_PI / 2.0f - 0.1f;
  if (settings.cameraPitch < -M_PI / 2.0f + 0.1f)
    settings.cameraPitch = -M_PI / 2.0f + 0.1f;
}
