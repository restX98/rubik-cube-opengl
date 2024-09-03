#include <Position.hpp>

Position::Position() {
  this->resetTransformation();
}

glm::mat4 Position::getModel() {
  if (!this->isDirty) {
    return this->model;
  }
  isDirty = false;

  glm::mat4 _model = glm::mat4(1.0f);

  _model = glm::translate(_model, this->translation);

  glm::mat4 xRotationMatrix = glm::mat4(1.0f);
  if (this->rotationAngleX != 0) {
    _model *= glm::rotate(xRotationMatrix, glm::radians(this->rotationAngleX), glm::vec3(this->rotationForceX, 0.0f, 0.0f));
  }
  glm::mat4 yRotationMatrix = glm::mat4(1.0f);
  if (this->rotationAngleY != 0) {
    _model *= glm::rotate(yRotationMatrix, glm::radians(this->rotationAngleY), glm::vec3(0.0f, this->rotationForceY, 0.0f));
  }
  glm::mat4 zRotationMatrix = glm::mat4(1.0f);
  if (this->rotationAngleZ != 0) {
    _model *= glm::rotate(zRotationMatrix, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, this->rotationForceZ));
  }

  this->model = glm::scale(_model, glm::vec3(this->scaling, this->scaling, this->scaling));

  return this->model;
}

void Position::translate() {
  this->translate(0.0f, 0.0f, 0.0f);
}
void Position::translate(float x, float y, float z) {
  this->translation = glm::vec3(x, y, z);
  this->isDirty = true;
}

void Position::resetRotation() {
  this->rotateX(0.0f);
  this->rotateY(0.0f);
  this->rotateZ(0.0f);
  this->isDirty = true;
}
void Position::rotateX(float angle, float force) {
  this->rotationAngleX = angle;
  this->rotationForceX = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}
void Position::rotateY(float angle, float force) {
  this->rotationAngleY = angle;
  this->rotationForceY = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}
void Position::rotateZ(float angle, float force) {
  this->rotationAngleZ = angle;
  this->rotationForceZ = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}

void Position::scale() {
  this->scale(1.0f);
}
void Position::scale(float scaling) {
  this->scaling = scaling;
  this->isDirty = true;
}

void Position::resetTransformation() {
  this->translate();
  this->resetRotation();
  this->scale();
}

void Position::setXAxis(glm::vec3 axis) {
  this->xAxis = axis;
}

void Position::setYAxis(glm::vec3 axis) {
  this->yAxis = axis;
}

void Position::setZAxis(glm::vec3 axis) {
  this->zAxis = axis;
}

glm::vec3 Position::getXAxis() {
  return this->xAxis;
}

glm::vec3 Position::getYAxis() {
  return this->yAxis;
}

glm::vec3 Position::getZAxis() {
  return this->zAxis;
}

glm::vec3 Position::getTranslation() {
  return this->translation;
}

float Position::getRotationAngleX() {
  return this->rotationAngleX;
}

float Position::getRotationAngleY() {
  return this->rotationAngleY;
}

float Position::getRotationAngleZ() {
  return this->rotationAngleZ;
}

float Position::getScaling() {
  return this->scaling;
}
