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
  this->leftFace = new Square(shader, Plane::YZ);
  this->rightFace = new Square(shader, Plane::YZ);
  this->topFace = new Square(shader, Plane::XZ);
  this->bottomFace = new Square(shader, Plane::XZ);
}

void Cube::transform() {
  glm::vec3 frontFaceTranslation = glm::vec3(0.0f, 0.0f, distanceToOrigin);
  glm::vec3 backFaceTranslation = glm::vec3(0.0f, 0.0f, -distanceToOrigin);
  glm::vec3 leftFaceTranslation = glm::vec3(-distanceToOrigin, 0.0f, 0.0f);
  glm::vec3 rightFaceTranslation = glm::vec3(distanceToOrigin, 0.0f, 0.0f);
  glm::vec3 topFaceTranslation = glm::vec3(0.0f, distanceToOrigin, 0.0f);
  glm::vec3 bottomFaceTranslation = glm::vec3(0.0f, -distanceToOrigin, 0.0f);

  this->relativeTransform(this->frontFace, frontFaceTranslation);
  this->relativeTransform(this->backFace, backFaceTranslation);
  this->relativeTransform(this->leftFace, leftFaceTranslation);
  this->relativeTransform(this->rightFace, rightFaceTranslation);
  this->relativeTransform(this->topFace, topFaceTranslation);
  this->relativeTransform(this->bottomFace, bottomFaceTranslation);
}

void Cube::relativeTransform(Square* face, glm::vec3 relativeTranslation) {
  glm::mat4 transformation = glm::mat4(1.0f);
  transformation = glm::scale(transformation, glm::vec3(this->scaling, this->scaling, this->scaling));
  transformation = glm::rotate(transformation, glm::radians(this->rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
  transformation = glm::rotate(transformation, glm::radians(this->rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
  transformation = glm::rotate(transformation, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
  relativeTranslation = glm::vec3(transformation * glm::vec4(relativeTranslation, 1.0f));

  face->translate(relativeTranslation + this->translation);
  face->rotateX(this->rotationAngleX);
  face->rotateY(this->rotationAngleY);
  face->rotateZ(this->rotationAngleZ);
  face->scale(this->scaling);
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
