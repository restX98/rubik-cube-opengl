#include <Cube.hpp>

Cube::Cube(Shader* shader) : Model(shader) {
  this->generateFaces();
}

void Cube::draw(float deltaTime) {
  this->transform();

  this->frontFace->draw();
  this->backFace->draw();
  this->leftFace->draw();
  this->rightFace->draw();
  this->topFace->draw();
  this->bottomFace->draw();
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
  this->topFace->translate(0.0f, -distanceToOrigin, 0.0f);
}


void Cube::translate(float x, float y, float z) {
  this->frontFace->setPivot(x, y, z);
  this->backFace->setPivot(x, y, z);
  this->leftFace->setPivot(x, y, z);
  this->rightFace->setPivot(x, y, z);
  this->topFace->setPivot(x, y, z);
  this->bottomFace->setPivot(x, y, z);
}

void Cube::rotateX(float angle, float force) {
  this->frontFace->rotateX(angle, force);
  this->backFace->rotateX(angle, force);
  this->leftFace->rotateX(angle, force);
  this->rightFace->rotateX(angle, force);
  this->topFace->rotateX(angle, force);
  this->bottomFace->rotateX(angle, force);
}

void Cube::rotateY(float angle, float force) {
  this->frontFace->rotateY(angle, force);
  this->backFace->rotateY(angle, force);
  this->leftFace->rotateY(angle, force);
  this->rightFace->rotateY(angle, force);
  this->topFace->rotateY(angle, force);
  this->bottomFace->rotateY(angle, force);
}

void Cube::rotateZ(float angle, float force) {
  this->frontFace->rotateZ(angle, force);
  this->backFace->rotateZ(angle, force);
  this->leftFace->rotateZ(angle, force);
  this->rightFace->rotateZ(angle, force);
  this->topFace->rotateZ(angle, force);
  this->bottomFace->rotateZ(angle, force);
}

void Cube::scale(float scaling) {
  this->frontFace->scale(scaling);
  this->backFace->scale(scaling);
  this->leftFace->scale(scaling);
  this->rightFace->scale(scaling);
  this->topFace->scale(scaling);
  this->bottomFace->scale(scaling);
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
