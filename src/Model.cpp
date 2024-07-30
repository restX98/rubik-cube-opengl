#include <Model.hpp>

Model::Model(Shader* shader) : shader(shader) {
  this->resetTransformation();
}

void Model::transform() {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, this->translation);

  glm::mat4 xRotationMatrix = glm::mat4(1.0f);
  if (this->rotationAngleX != 0) {
    model *= glm::rotate(xRotationMatrix, glm::radians(this->rotationAngleX), glm::vec3(this->rotationForceX, 0.0f, 0.0f));
  }
  glm::mat4 yRotationMatrix = glm::mat4(1.0f);
  if (this->rotationAngleY != 0) {
    model *= glm::rotate(yRotationMatrix, glm::radians(this->rotationAngleY), glm::vec3(0.0f, this->rotationForceY, 0.0f));
  }
  glm::mat4 zRotationMatrix = glm::mat4(1.0f);
  if (this->rotationAngleZ != 0) {
    model *= glm::rotate(zRotationMatrix, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, this->rotationForceZ));
  }

  model = glm::scale(model, glm::vec3(this->scaling, this->scaling, this->scaling));

  this->shader->setMat4("model", model);
}

void Model::translate() {
  this->translate(glm::vec3(0.0f));
}
void Model::translate(glm::vec3 translation) {
  this->translation = translation;
}

void Model::resetRotation() {
  this->rotateX(0.0f);
  this->rotateY(0.0f);
  this->rotateZ(0.0f);
}
void Model::rotateX(float angle, float force) {
  this->rotationAngleX = angle;
  this->rotationForceX = force > 1.0f ? 1.0f : force;
}
void Model::rotateY(float angle, float force) {
  this->rotationAngleY = angle;
  this->rotationForceY = force > 1.0f ? 1.0f : force;
}
void Model::rotateZ(float angle, float force) {
  this->rotationAngleZ = angle;
  this->rotationForceZ = force > 1.0f ? 1.0f : force;
}

void Model::scale() {
  this->scale(1.0f);
}
void Model::scale(float scaling) {
  this->scaling = scaling;
}

void Model::resetTransformation() {
  this->translate();
  this->resetRotation();
  this->scale();
  this->rotationAngleX = 0;
}

void Model::draw() {}
