#include <Model.hpp>

Model::Model(Shader* shader) : shader(shader), position(new Position()) {}

Model::~Model() {
  delete position;
}

void Model::transform() {
  this->shader->setMat4("model", this->position->getModel());
}

void Model::draw(float deltaTime) {}

void Model::setPivot(float x, float y, float z) {
  RelativePosition* newPosix = new RelativePosition(*this->position, glm::vec3(x, y, z));

  delete this->position;
  this->position = newPosix;
}

void Model::removePivot() {
  Position* newPosix = new Position(*this->position);

  delete this->position;
  this->position = newPosix;
}

void Model::translate(float x, float y, float z) {
  this->position->translate(x, y, z);
  this->isDirty = true;
}

void Model::rotateX(float angle, float force) {
  this->position->rotateX(angle, force);
  this->isDirty = true;
}
void Model::rotateY(float angle, float force) {
  this->position->rotateY(angle, force);
  this->isDirty = true;
}
void Model::rotateZ(float angle, float force) {
  this->position->rotateZ(angle, force);
  this->isDirty = true;
}

void Model::scale(float scaling) {
  this->position->scale(scaling);
  this->isDirty = true;
}
