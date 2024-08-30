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

  _model *= glm::mat4(glm::quat(glm::radians(glm::vec3(this->rotationAngleX, this->rotationAngleY, this->rotationAngleZ))));

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
