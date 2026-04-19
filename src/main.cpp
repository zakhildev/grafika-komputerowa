#include "include/Mesh.hpp"
#include <string>
#define GLM_FORCE_RADIANS
#define STB_IMAGE_IMPLEMENTATION

#include "./include/Callbacks.hpp"
#include "./include/Settings.hpp"
#include "./include/stb_image.h"
#include "include/Model.hpp"
#include "include/Shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_u_char.h>
#include <sys/_types/_u_int.h>
#include <sys/types.h>

using namespace glm;
using namespace std;
using namespace Assimp;

void initOpenGLProgram(GLFWwindow *window) {
  stbi_set_flip_vertically_on_load(true);
  settings.loadFromFile("settings.conf");
  glfwSetCursorPosCallback(window, Callbacks::mouse_callback);
  glfwSetErrorCallback(Callbacks::error_callback);
  glfwSetKeyCallback(window, Callbacks::key_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void updateCameraMovement() {
  // Calculate forward vector from yaw only (no pitch for vertical movement)
  vec3 forward(sin(settings.cameraYaw), 0.0f, cos(settings.cameraYaw));

  // Right vector (perpendicular to forward, in horizontal plane)
  vec3 right(sin(settings.cameraYaw + M_PI / 2.0f), 0.0f,
             cos(settings.cameraYaw + M_PI / 2.0f));

  // Up vector
  vec3 up(0.0f, 1.0f, 0.0f);

  // W - forward
  if (settings.keys[GLFW_KEY_W]) {
    settings.cameraPos += forward * settings.cameraSpeed;
  }
  // S - backward
  if (settings.keys[GLFW_KEY_S]) {
    settings.cameraPos -= forward * settings.cameraSpeed;
  }
  // A - left
  if (settings.keys[GLFW_KEY_A]) {
    settings.cameraPos += right * settings.cameraSpeed;
  }
  // D - right
  if (settings.keys[GLFW_KEY_D]) {
    settings.cameraPos -= right * settings.cameraSpeed;
  }
}

int main(void) {
  GLFWwindow *window;
  Importer importer;

  if (!glfwInit()) {
    fprintf(stderr, "Can't initialize GLFW.\n");
    exit(EXIT_FAILURE);
  }

  // MacOS requires to specify OpenGL version and profile
#ifdef __APPLE__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  // Disable window resizing to simplify things
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(1080, 1080, "Alcohol Gallery", NULL, NULL);

  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  GLenum err;
  if ((err = glewInit()) != GLEW_OK) {
    fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
    exit(EXIT_FAILURE);
  }

  initOpenGLProgram(window);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    updateCameraMovement();
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static Shader defautlShader("shaders/default.vert", "shaders/default.frag");

    static Model pedestal("models/pedestal/pedestal.obj");

    static vector<Model> bottles = {};
    static bool bottlesLoaded = false;
    if (!bottlesLoaded) {
      for (int i = 1; i <= 3; i++) {
        string path = "models/bottles/bottle" + to_string(i) + ".obj";
        Model bottle(path.c_str());
        bottles.push_back(bottle);
      }
    }
    bottlesLoaded = true;

    static mat4 P = perspective(radians(50.0f), 1.0f, 0.1f, 50.0f);

    mat4 V =
        lookAt(settings.cameraPos,
               settings.cameraPos +
                   vec3(sin(settings.cameraYaw) * cos(settings.cameraPitch),
                        sin(settings.cameraPitch),
                        cos(settings.cameraYaw) * cos(settings.cameraPitch)),
               vec3(0.0f, 1.0f, 0.0f));

    defautlShader.use();
    defautlShader.setMat4("P", P);
    defautlShader.setMat4("V", V);
    defautlShader.setVec3("viewPos", settings.cameraPos);

    // Bottles and pedestal rednering
    for (int i = 0; i < 10; i++) {
      mat4 M = mat4(1.0f);
      if (i <= 4) {
        M = translate(M, vec3(-5.0f + (i * 2.5f), 0.0f, 3.0f));
      } else {
        M = translate(M, vec3(-5.0f + ((i - 5) * 2.5f), 0.0f, -3.0f));
      }

      defautlShader.setMat4("M", M);
      pedestal.Draw(defautlShader);

      M = translate(M, vec3(0.0f, 0.8f, 0.0f));
      defautlShader.setMat4("M", M);
      bottles[i % bottles.size()].Draw(defautlShader);
    }

    // Floor rendering (texcoord multiplied by 8 to "shrink" the texture)
    vector<Vertex> floorVertices = {
        {{-8.0f, 0.0f, -6.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{8.0f, 0.0f, -6.0f}, {0.0f, 1.0f, 0.0f}, {8.0f, 0.0f}},
        {{8.0f, 0.0f, 6.0f}, {0.0f, 1.0f, 0.0f}, {8.0f, 6.0f}},
        {{-8.0f, 0.0f, 6.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 6.0f}}};

    vector<uint> floorIndices = {0, 1, 2, 0, 2, 3};

    // Texture loaded from png file not from model data
    // Maked as static to load only once
    static vector<Texture> floorTextures = {
        {TextureFromFile("floor.png", "textures"), "diffuse", "floor.png"}};

    Mesh floor(floorVertices, floorIndices, floorTextures);
    mat4 floorM = mat4(1.0f);
    floorM = translate(floorM, vec3(0.0f, -1.0f, 0.0f));
    defautlShader.setMat4("M", floorM);
    floor.Draw(defautlShader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window); // Delete OpenGL context and the window.
  glfwTerminate();           // Free GLFW resources
  exit(EXIT_SUCCESS);
}
