/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define GLM_FORCE_RADIANS

#include "./include/Cube.h"
#include "./include/ShaderProgram.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace glm;
using namespace std;
using namespace SimpleModels;

void error_callback(int error, const char *description) {
  fputs(description, stderr);
}

void initOpenGLProgram(GLFWwindow *window) {
  initShaders();
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void freeOpenGLProgram(GLFWwindow *window) { freeShaders(); }

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void drawFinger(mat4 base, float rotationDeg) {
  static Cube c;
  mat4 fingerSegment = base;
  fingerSegment =
      rotate(fingerSegment, radians(-rotationDeg), vec3(0.0f, 0.0f, 1.0f));
  fingerSegment = translate(fingerSegment, vec3(1.0f, 0.0f, 0.0f));
  fingerSegment = scale(fingerSegment, vec3(1.0f, 0.25f, 0.5f));
  glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(fingerSegment));
  glUniform4f(spLambert->u("color"), 1.0f, 0.0f, 0.0f, 1.0f);
  c.drawSolid();
  fingerSegment = translate(fingerSegment, vec3(1.0f, 0.0f, 0.0f));

  mat4 fingerSegment2 = fingerSegment;
  // przywracamy skalę, aby translacja i rotacja działały poprawnie
  fingerSegment2 = scale(fingerSegment2, vec3(1.0f, 4.0f, 2.0f));
  fingerSegment2 =
      rotate(fingerSegment2, radians(-rotationDeg), vec3(0.0f, 0.0f, 1.0f));
  fingerSegment2 = translate(fingerSegment2, vec3(1.0f, 0.0f, 0.0f));
  fingerSegment2 = scale(fingerSegment2, vec3(1.0f, 0.25f, 0.5f));
  glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(fingerSegment2));
  glUniform4f(spLambert->u("color"), 0.0f, 1.0f, 0.0f, 1.0f);
  c.drawSolid();
  fingerSegment2 = translate(fingerSegment2, vec3(1.0f, 0.0f, 0.0f));

  mat4 fingerSegment3 = fingerSegment2;
  // przywracamy skalę, aby translacja i rotacja działały poprawnie
  fingerSegment3 = scale(fingerSegment3, vec3(1.0f, 4.0f, 2.0f));
  fingerSegment3 =
      rotate(fingerSegment3, radians(-rotationDeg), vec3(0.0f, 0.0f, 1.0f));
  fingerSegment3 = translate(fingerSegment3, vec3(1.0f, 0.0f, 0.0f));
  fingerSegment3 = scale(fingerSegment3, vec3(1.0f, 0.25f, 0.5f));
  glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(fingerSegment3));
  glUniform4f(spLambert->u("color"), 0.0f, 0.0f, 1.0f, 1.0f);
  c.drawSolid();
}

int main(void) {
  GLFWwindow *window;

  glfwSetErrorCallback(error_callback);

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

  window = glfwCreateWindow(720, 720, "Alcohol Gallery", NULL, NULL);

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

  // Projection matrix is fixed
  static mat4 P = perspective(radians(50.0f), 1.0f, 1.0f, 50.0f);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Zadanie na laby: Rysowanie ręki robota
    static Cube c;

    mat4 V = lookAt(vec3(-10.0f, -2.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f),
                    vec3(0.0f, 1.0f, 0.0f));

    spLambert->use();
    glUniformMatrix4fv(spLambert->u("P"), 1, false, value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"), 1, false, value_ptr(V));
    glUniform4f(spLambert->u("color"), 1.0f, 0.0f, 1.0f, 1.0f);

    // Dłoń
    mat4 metacarpus = mat4(1.0f);
    metacarpus = scale(metacarpus, vec3(0.5f, 0.25f, 0.5f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(metacarpus));
    glUniform4f(spLambert->u("color"), 1.0f, 1.0f, 1.0f, 1.0f);
    c.drawSolid();

    // Palce
    // Kąt zginania palców zmienia się w czasie
    float bendingAngle = (sin(glfwGetTime()) + 1.0f) * 20.0f;
    for (float deg = 0.0f; deg < 360.0f; deg += 90.0f) {
      mat4 fingerBase =
          rotate(mat4(1.0f), radians(deg), vec3(0.0f, 1.0f, 0.0f));
      fingerBase = translate(fingerBase, vec3(0.5f, 0.0f, 0.0f));
      drawFinger(fingerBase, bendingAngle);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  freeOpenGLProgram(window);

  glfwDestroyWindow(window); // Delete OpenGL context and the window.
  glfwTerminate();           // Free GLFW resources
  exit(EXIT_SUCCESS);
}
