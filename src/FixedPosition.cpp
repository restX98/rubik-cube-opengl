#include <FixedPosition.hpp>

FixedPosition::FixedPosition(glm::vec3 pivot) : Position(), pivot(pivot) {}

FixedPosition::FixedPosition(Position position, glm::vec3 pivot) : Position(position), pivot(pivot) {}

glm::mat4 FixedPosition::getModel() {
  return this->model;
}

void FixedPosition::translate(float x, float y, float z) {
  this->translation = glm::vec3(x, y, z);
  this->model = glm::translate(this->model, glm::vec3(x, y, z));
}

void FixedPosition::rotateX(float angle, float force) {
  this->rotationAngleX += angle;
  if (this->rotationAngleX >= 90.0f) {
    this->rotationAngleX -= 90.0f;
  } else if (this->rotationAngleX <= -90.0f) {
    this->rotationAngleX += 90.0f;
  }

  this->model = glm::translate(this->model, -this->translation);
  this->model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->xAxis) * this->model;

  this->model = glm::translate(this->model, this->translation);
}

void FixedPosition::rotateY(float angle, float force) {
  this->rotationAngleY += angle;
  if (this->rotationAngleY >= 90.0f) {
    this->rotationAngleY -= 90.0f;
  } else if (this->rotationAngleY <= -90.0f) {
    this->rotationAngleY += 90.0f;
  }

  this->model = glm::translate(this->model, -this->translation);
  this->model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->yAxis) * this->model;
  this->model = glm::translate(this->model, this->translation);
}

void FixedPosition::rotateZ(float angle, float force) {
  this->rotationAngleZ += angle;
  if (this->rotationAngleZ >= 90.0f) {
    this->rotationAngleZ -= 90.0f;
  } else if (this->rotationAngleZ <= -90.0f) {
    this->rotationAngleZ += 90.0f;
  }

  this->model = glm::translate(this->model, -this->translation);

  this->model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->zAxis) * this->model;

  this->model = glm::translate(this->model, this->translation);
}
