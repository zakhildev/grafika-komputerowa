#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Callbacks {

void error_callback(int error, const char *description);
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
} // namespace Callbacks