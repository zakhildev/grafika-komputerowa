#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

// Domyślne wartości
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
  // Atrybuty kamery
  vec3 Position;
  vec3 Front;
  vec3 Up;
  vec3 Right;
  vec3 WorldUp;
  // Kąty Eulera
  float Yaw;
  float Pitch;
  // Opcje kamery
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  // Konstruktor z wektorami
  Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f),
         vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);

  // Zwraca macierz widoku obliczoną za pomocą kątów Eulera i macierzy LookAt
  mat4 GetViewMatrix();

  // Przetwarza wejście z klawiatury
  void ProcessKeyboard(Camera_Movement direction, float deltaTime);

  // Przetwarza wejście z myszy
  void ProcessMouseMovement(float xoffset, float yoffset,
                            GLboolean constrainPitch = true);

private:
  // Oblicza wektory Front, Right i Up na podstawie kątów Eulera
  void updateCameraVectors();
};