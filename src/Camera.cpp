#include "Camera.hpp"

Camera::Camera(Shader& shader) : shader(shader) {
  this->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

  this->projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

void Camera::update() {
  glm::vec3 direction;
  direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
  direction.y = sin(glm::radians(this->pitch));
  direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
  this->cameraFront = glm::normalize(direction);

  glm::mat4 view = glm::lookAt(
    this->cameraPos,
    this->cameraPos + this->cameraFront,
    this->cameraUp
  );
  this->shader.setMat4("view", view);

  this->shader.setMat4("projection", this->projection);
}

void Camera::moveForward(float delta) {
  this->cameraPos += this->cameraFront * speed * delta;
}

void Camera::moveBackward(float delta) {
  this->cameraPos -= this->cameraFront * speed * delta;
}

void Camera::moveLeft(float delta) {
  this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * speed * delta;
}

void Camera::moveRight(float delta) {
  this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * speed * delta;
}

void Camera::lookAround(float xOffset, float yOffset) {
  yaw += xOffset * this->moveSensitivity;
  pitch += yOffset * this->moveSensitivity;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;
}
