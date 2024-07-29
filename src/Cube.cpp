#include <Cube.hpp>

Cube::Cube(Shader* shader) : Model(shader) {
  this->generateFaces();
}

void Cube::draw() {
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
  this->backFace = new Square(shader);
  this->leftFace = new Square(shader);
  this->rightFace = new Square(shader);
  this->topFace = new Square(shader);
  this->bottomFace = new Square(shader);
}

void Cube::transform() {
  this->frontFace->translate(glm::vec3(0.0f, 0.0f, 0.5f) + this->translation);
  this->frontFace->rotate(this->rotationAngle, this->rotationAxis);
  this->frontFace->scale(this->scaling);

  this->backFace->translate(glm::vec3(0.0f, 0.0f, -0.5f) + this->translation);
  this->backFace->rotate(this->rotationAngle, this->rotationAxis);
  this->backFace->scale(this->scaling);

  this->leftFace->translate(glm::vec3(-0.5f, 0.0f, 0.0f) + this->translation);
  this->leftFace->rotate(90.0f + this->rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f) + this->rotationAxis);
  this->leftFace->scale(this->scaling);

  this->rightFace->translate(glm::vec3(0.5f, 0.0f, 0.0f) + this->translation);
  this->rightFace->rotate(90.0f + this->rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f) + this->rotationAxis);
  this->rightFace->scale(this->scaling);

  this->topFace->translate(glm::vec3(0.0f, 0.5f, 0.0f) + this->translation);
  this->topFace->rotate(90.0f + this->rotationAngle, glm::vec3(1.0f, 0.0f, 0.0f) + this->rotationAxis);
  this->topFace->scale(this->scaling);

  this->bottomFace->translate(glm::vec3(0.0f, -0.5f, 0.0f) + this->translation);
  this->bottomFace->rotate(90.0f + this->rotationAngle, glm::vec3(1.0f, 0.0f, 0.0f) + this->rotationAxis);
  this->bottomFace->scale(this->scaling);
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
    this->topFace->setColor(color);
    return;
  }
}
