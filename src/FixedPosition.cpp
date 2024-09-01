#include <FixedPosition.hpp>

#include <iostream>

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

void FixedPosition::reversXY(bool clockwise) {
  std::cout << "BEFORE: X (" << xAxis.x << "," << xAxis.y << "," << xAxis.z << ")" << std::endl;
  std::cout << "BEFORE: Y (" << yAxis.x << "," << yAxis.y << "," << yAxis.z << ")" << std::endl;
  std::cout << "BEFORE: Z (" << zAxis.x << "," << zAxis.y << "," << zAxis.z << ")" << std::endl;
  glm::vec3 tmp = this->xAxis;
  if (clockwise) {
    this->xAxis = this->yAxis;
    this->yAxis = -tmp;
  } else {
    this->xAxis = -this->yAxis;
    this->yAxis = tmp;
  }
  std::cout << "AFTER: X (" << xAxis.x << "," << xAxis.y << "," << xAxis.z << ")" << std::endl;
  std::cout << "AFTER: Y (" << yAxis.x << "," << yAxis.y << "," << yAxis.z << ")" << std::endl;
  std::cout << "AFTER: Z (" << zAxis.x << "," << zAxis.y << "," << zAxis.z << ")" << std::endl;
}

void FixedPosition::reversXZ(bool clockwise) {
  std::cout << "BEFORE: X (" << xAxis.x << "," << xAxis.y << "," << xAxis.z << ")" << std::endl;
  std::cout << "BEFORE: Y (" << yAxis.x << "," << yAxis.y << "," << yAxis.z << ")" << std::endl;
  std::cout << "BEFORE: Z (" << zAxis.x << "," << zAxis.y << "," << zAxis.z << ")" << std::endl;

  glm::vec3 tmp = this->xAxis;
  if (clockwise) {
    this->xAxis = this->zAxis;
    this->zAxis = -tmp;
  } else {
    this->xAxis = -this->zAxis;
    this->zAxis = tmp;
  }
  std::cout << "AFTER: X (" << xAxis.x << "," << xAxis.y << "," << xAxis.z << ")" << std::endl;
  std::cout << "AFTER: Y (" << yAxis.x << "," << yAxis.y << "," << yAxis.z << ")" << std::endl;
  std::cout << "AFTER: Z (" << zAxis.x << "," << zAxis.y << "," << zAxis.z << ")" << std::endl;
}

void FixedPosition::reversYZ(bool clockwise) {
  std::cout << "BEFORE: X (" << xAxis.x << "," << xAxis.y << "," << xAxis.z << ")" << std::endl;
  std::cout << "BEFORE: Y (" << yAxis.x << "," << yAxis.y << "," << yAxis.z << ")" << std::endl;
  std::cout << "BEFORE: Z (" << zAxis.x << "," << zAxis.y << "," << zAxis.z << ")" << std::endl;
  glm::vec3 tmp = this->zAxis;
  if (clockwise) {
    this->zAxis = -this->yAxis;
    this->yAxis = tmp;
  } else {
    this->zAxis = this->yAxis;
    this->yAxis = -tmp;
  }
  std::cout << "AFTER: X (" << xAxis.x << "," << xAxis.y << "," << xAxis.z << ")" << std::endl;
  std::cout << "AFTER: Y (" << yAxis.x << "," << yAxis.y << "," << yAxis.z << ")" << std::endl;
  std::cout << "AFTER: Z (" << zAxis.x << "," << zAxis.y << "," << zAxis.z << ")" << std::endl;
}
