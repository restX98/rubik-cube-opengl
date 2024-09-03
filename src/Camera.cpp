#include "Camera.hpp"

Camera::Camera(Shader& shader, int width, int height) : shader(shader), width(width), height(height), AnimatedModel(&shader) {
  this->positions[0] = glm::vec3(0.0f, 0.0f, 15.0f);  // Normal Position
  // Reverse Position
  this->positions[1] = glm::vec4(this->positions[0], 1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));

  this->cameraInitialPos = this->positions[0];
  this->cameraPos = this->cameraInitialPos;
  this->cameraFront = glm::normalize(-this->cameraPos);
  this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

  this->projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f, 100.0f);
}

void Camera::draw(glm::mat4 model) {
  this->cameraFront = glm::normalize(-this->cameraPos);

  glm::mat4 view = glm::lookAt(
    this->cameraPos,
    this->cameraPos + this->cameraFront,
    this->cameraUp
  );
  this->shader.setMat4("view", view);

  this->shader.setMat4("projection", this->projection);
}

void Camera::draw(float deltaTime, glm::mat4 model) {
  if (this->transition) {
    this->transition->update(deltaTime);
  }
  this->lookAround();
  this->draw();
}

void Camera::lookAround() {
  float angleDegrees = glm::mix(-60.0f, 60.0f, static_cast<float>(this->yPos) / this->height);
  float angleRadians = glm::radians(angleDegrees);

  glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angleRadians, glm::vec3(1.0f, 0.0f, 0.0f));

  angleDegrees = glm::mix(-60.0f, 60.0f, static_cast<float>(this->xPos) / width);
  angleRadians = glm::radians(angleDegrees);

  rotationMatrix = glm::rotate(rotationMatrix, angleRadians, glm::vec3(0.0f, 1.0f, 0.0f));

  this->cameraPos = glm::vec4(this->cameraInitialPos, 1.0f) * rotationMatrix;
}

void Camera::setView(State state) {
  this->cameraInitialPos = this->positions[static_cast<int>(state)];
  if (state == State::NORMAL) {
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  } else {
    this->cameraUp = glm::vec3(0.0f, -1.0f, 0.0f);
  }
}

void Camera::setWindowSize(int width, int height) {
  this->height = height;
  this->width = width;
}

void Camera::setMouseCoords(int xPos, int yPos) {
  this->xPos = std::clamp(xPos, 0, this->width);
  this->yPos = std::clamp(yPos, 0, this->height);
}
