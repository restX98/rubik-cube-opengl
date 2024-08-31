#include <RelativePosition.hpp>

RelativePosition::RelativePosition(glm::vec3 pivot) : Position(), pivot(pivot) {}

RelativePosition::RelativePosition(Position position, glm::vec3 pivot) : Position(position), pivot(pivot) {}

glm::mat4 RelativePosition::getModel() {
  if (!this->isDirty) {
    return this->model;
  }
  isDirty = false;

  glm::mat4 _model = glm::mat4(1.0f);
  _model = glm::translate(_model, this->pivot);

  _model = glm::scale(_model, glm::vec3(this->scaling, this->scaling, this->scaling));

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

  _model = glm::translate(_model, -this->pivot);

  this->model = glm::translate(_model, this->translation);

  return this->model;
}

void RelativePosition::rotateX(float angle, float force) {
  this->rotationAngleX += angle;
  this->rotationForceX = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}


void RelativePosition::rotateY(float angle, float force) {
  this->rotationAngleY += angle;
  this->rotationForceY = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}

void RelativePosition::rotateZ(float angle, float force) {
  this->rotationAngleZ += angle;
  this->rotationForceZ = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}
