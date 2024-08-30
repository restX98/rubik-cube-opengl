#include <Model.hpp>

Model::Model(Shader* shader) : shader(shader) {
  this->resetTransformation();
}

void Model::transform() {
  if (!isDirty) {
    this->shader->setMat4("model", model);
    return;
  };
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

  this->shader->setMat4("model", this->model);
}

void Model::translate() {
  this->translate(glm::vec3(0.0f));
}
void Model::translate(glm::vec3 translation) {
  this->translation = translation;
  this->isDirty = true;
}

void Model::resetRotation() {
  this->rotateX(0.0f);
  this->rotateY(0.0f);
  this->rotateZ(0.0f);
  this->isDirty = true;
}
void Model::rotateX(float angle, float force) {
  this->rotationAngleX = angle;
  this->rotationForceX = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}
void Model::rotateY(float angle, float force) {
  this->rotationAngleY = angle;
  this->rotationForceY = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}
void Model::rotateZ(float angle, float force) {
  this->rotationAngleZ = angle;
  this->rotationForceZ = force > 1.0f ? 1.0f : force;
  this->isDirty = true;
}

void Model::scale() {
  this->scale(1.0f);
}
void Model::scale(float scaling) {
  this->scaling = scaling;
  this->isDirty = true;
}

void Model::resetTransformation() {
  this->translate();
  this->resetRotation();
  this->scale();
}

void Model::draw(float deltaTime) {}
