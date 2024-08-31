#include <Cube.hpp>

Cube::Cube(Shader* shader) : Model(shader) {
  this->generateFaces();
}

// void Cube::draw() {
//   std::vector<glm::mat4> models;
//   models.push_back(this->position->getModel());

//   this->frontFace->draw(models);
//   this->backFace->draw(models);
//   this->leftFace->draw(models);
//   this->rightFace->draw(models);
//   this->topFace->draw(models);
//   this->bottomFace->draw(models);
// }

void Cube::draw(glm::mat4 model) {
  // models.push_back(this->position->getModel());
  glm::mat4 _model = model * this->position->getModel();

  this->frontFace->draw(_model);
  this->backFace->draw(_model);
  this->leftFace->draw(_model);
  this->rightFace->draw(_model);
  this->topFace->draw(_model);
  this->bottomFace->draw(_model);
}

void Cube::generateFaces() {
  this->frontFace = new Square(shader);
  this->frontFace->setPivot(0.0f, 0.0f, 0.0f);
  this->frontFace->translate(0.0f, 0.0f, distanceToOrigin);

  this->backFace = new Square(shader);
  this->backFace->setPivot(0.0f, 0.0f, 0.0f);
  this->backFace->translate(0.0f, 0.0f, -distanceToOrigin);

  this->leftFace = new Square(shader, Plane::YZ);
  this->leftFace->setPivot(0.0f, 0.0f, 0.0f);
  this->leftFace->translate(-distanceToOrigin, 0.0f, 0.0f);

  this->rightFace = new Square(shader, Plane::YZ);
  this->rightFace->setPivot(0.0f, 0.0f, 0.0f);
  this->rightFace->translate(distanceToOrigin, 0.0f, 0.0f);

  this->topFace = new Square(shader, Plane::XZ);
  this->topFace->setPivot(0.0f, 0.0f, 0.0f);
  this->topFace->translate(0.0f, distanceToOrigin, 0.0f);

  this->bottomFace = new Square(shader, Plane::XZ);
  this->bottomFace->setPivot(0.0f, 0.0f, 0.0f);
  this->bottomFace->translate(0.0f, -distanceToOrigin, 0.0f);
}


void Cube::translate(float x, float y, float z) {
  this->frontFace->setPivot(x, y, z);
  this->backFace->setPivot(x, y, z);
  this->leftFace->setPivot(x, y, z);
  this->rightFace->setPivot(x, y, z);
  this->topFace->setPivot(x, y, z);
  this->bottomFace->setPivot(x, y, z);

  this->position->translate(x, y, z);
}

void Cube::rotateX(float angle, float force) {
  this->position->rotateX(angle, force);
}

void Cube::rotateY(float angle, float force) {
  this->position->rotateY(angle, force);
}

void Cube::rotateZ(float angle, float force) {
  this->position->rotateZ(angle, force);

}

void Cube::scale(float scaling) {
  this->position->scale(scaling);
}

void Cube::setFaceColor(Face face, glm::vec3 color) {
  switch (face) {
  case Face::FRONT_FACE:
    this->frontFace->setColor(color);
    return;
  case Face::BACK_FACE:
    this->backFace->setColor(color);
    return;
  case Face::LEFT_FACE:
    this->leftFace->setColor(color);
    return;
  case Face::RIGHT_FACE:
    this->rightFace->setColor(color);
    return;
  case Face::TOP_FACE:
    this->topFace->setColor(color);
    return;
  case Face::BOTTOM_FACE:
    this->bottomFace->setColor(color);
    return;
  }
}
