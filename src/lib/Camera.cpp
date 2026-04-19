#include "../include/Camera.hpp"

using namespace glm;

Camera::Camera(vec3 position, vec3 up, float yaw, float pitch)
    : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
  Position = position;
  WorldUp = up;
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
}

mat4 Camera::GetViewMatrix() { return lookAt(Position, Position + Front, Up); }

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = MovementSpeed * deltaTime;
  // Uwzględnienie tylko osi XZ dla ruchu (tak jak miałeś w main.cpp)
  vec3 horizontalFront = normalize(vec3(Front.x, 0.0f, Front.z));
  vec3 horizontalRight = normalize(vec3(Right.x, 0.0f, Right.z));

  if (direction == FORWARD)
    Position += horizontalFront * velocity;
  if (direction == BACKWARD)
    Position -= horizontalFront * velocity;
  if (direction == LEFT)
    Position -= horizontalRight * velocity;
  if (direction == RIGHT)
    Position += horizontalRight * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrainPitch) {
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  if (constrainPitch) {
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
  }

  updateCameraVectors();
}

void Camera::updateCameraVectors() {
  // Obliczanie nowego wektora Front
  vec3 front;
  front.x = cos(radians(Yaw)) * cos(radians(Pitch));
  front.y = sin(radians(Pitch));
  front.z = sin(radians(Yaw)) * cos(radians(Pitch));
  Front = normalize(front);
  // Ponowne obliczenie wektorów Right i Up
  Right = normalize(cross(Front, WorldUp));
  Up = normalize(cross(Right, Front));
}