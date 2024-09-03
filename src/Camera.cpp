#include "Camera.hpp"

Camera::Camera(Shader& shader, float width, float height) : shader(shader), width(width), height(height) {
  this->cameraPos = glm::vec3(0.0f, 0.0f, 15.0f);
  this->cameraInitialPos = this->cameraPos;
  this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

  this->projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
}

void Camera::update() {
  this->cameraFront = glm::normalize(-this->cameraPos);

  glm::mat4 view = glm::lookAt(
    this->cameraPos,
    this->cameraPos + this->cameraFront,
    this->cameraUp
  );
  this->shader.setMat4("view", view);

  this->shader.setMat4("projection", this->projection);
}

void Camera::lookAround(float xPos, float yPos) {
  yPos = glm::clamp(yPos, 0.0f, this->height);
  float angleDegrees = glm::mix(-60.0f, 60.0f, yPos / this->height);
  float angleRadians = glm::radians(angleDegrees);

  glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angleRadians, glm::vec3(1.0f, 0.0f, 0.0f));

  yPos = glm::clamp(xPos, 0.0f, this->height);
  angleDegrees = glm::mix(-60.0f, 60.0f, xPos / this->width);
  angleRadians = glm::radians(angleDegrees);

  rotationMatrix = glm::rotate(rotationMatrix, angleRadians, glm::vec3(0.0f, 1.0f, 0.0f));

  this->cameraPos = glm::vec4(this->cameraInitialPos, 1.0f) * rotationMatrix;
}

void Camera::setHeight(int height) {
  this->height = height;
}
void Camera::setWidth(int width) {
  this->width = width;
}
