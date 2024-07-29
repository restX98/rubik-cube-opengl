#include <Model.hpp>

Model::Model(Shader* shader) : shader(shader) {
  this->resetTransformation();
}

void Model::transform() {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, this->translation);
  if (this->rotationAngle != 0) {
    model = glm::rotate(model, glm::radians(this->rotationAngle), this->rotationAxis);
  }
  model = glm::scale(model, this->scaling);

  this->shader->setMat4("model", model);
}

void Model::translate() {
  this->translate(glm::vec3(0.0f));
}
void Model::translate(glm::vec3 translation) {
  this->translation = translation;
}

void Model::rotate() {
  this->rotate(0.0f, glm::vec3(0.0f));
}
void Model::rotate(float angle, glm::vec3 axis) {
  this->rotationAngle = angle;
  this->rotationAxis = axis;
}

void Model::scale() {
  this->scale(glm::vec3(1.0f));
}
void Model::scale(glm::vec3 scaling) {
  this->scaling = scaling;
}

void Model::resetTransformation() {
  this->translate();
  this->rotate();
  this->scale();
}

void Model::draw() {}
