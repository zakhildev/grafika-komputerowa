#include "../include/Callbacks.hpp"
#include "../include/Camera.hpp"
#include "../include/Settings.hpp"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

extern Camera camera;

void Callbacks::error_callback(int error, const char *description) {
  fputs(description, stderr);
}

void Callbacks::key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);

  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
      settings.keys[key] = true;
    else if (action == GLFW_RELEASE)
      settings.keys[key] = false;
  }
}

void Callbacks::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  static float lastX = 540.0f, lastY = 540.0f;
  static bool firstMouse = true;

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // Odwrócone, bo Y rośnie w dół
  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}
