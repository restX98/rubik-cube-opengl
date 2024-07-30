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

  if (this->scaling != 1) {
    float scalingTranslation = (distanceToOrigin * this->scaling) - (distanceToOrigin);
    frontFaceTranslation.z += scalingTranslation;
    backFaceTranslation.z -= scalingTranslation;
    leftFaceTranslation.x -= scalingTranslation;
    rightFaceTranslation.x += scalingTranslation;
    topFaceTranslation.y += scalingTranslation;
    bottomFaceTranslation.y -= scalingTranslation;
  }

  // TODO: DRY
  glm::mat4 backFaceTransformation = glm::mat4(1.0f);
  backFaceTransformation = glm::rotate(backFaceTransformation, glm::radians(this->rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
  backFaceTransformation = glm::rotate(backFaceTransformation, glm::radians(this->rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
  backFaceTransformation = glm::rotate(backFaceTransformation, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
  backFaceTranslation = glm::vec3(backFaceTransformation * glm::vec4(backFaceTranslation, 1.0f));

  glm::mat4 frontFaceTransformation = glm::mat4(1.0f);
  frontFaceTransformation = glm::rotate(frontFaceTransformation, glm::radians(this->rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
  frontFaceTransformation = glm::rotate(frontFaceTransformation, glm::radians(this->rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
  frontFaceTransformation = glm::rotate(frontFaceTransformation, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
  frontFaceTranslation = glm::vec3(frontFaceTransformation * glm::vec4(frontFaceTranslation, 1.0f));

  glm::mat4 leftFaceTransformation = glm::mat4(1.0f);
  leftFaceTransformation = glm::rotate(leftFaceTransformation, glm::radians(this->rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
  leftFaceTransformation = glm::rotate(leftFaceTransformation, glm::radians(this->rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
  leftFaceTransformation = glm::rotate(leftFaceTransformation, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
  leftFaceTranslation = glm::vec3(leftFaceTransformation * glm::vec4(leftFaceTranslation, 1.0f));

  glm::mat4 rightFaceTransformation = glm::mat4(1.0f);
  rightFaceTransformation = glm::rotate(rightFaceTransformation, glm::radians(this->rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
  rightFaceTransformation = glm::rotate(rightFaceTransformation, glm::radians(this->rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
  rightFaceTransformation = glm::rotate(rightFaceTransformation, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
  rightFaceTranslation = glm::vec3(rightFaceTransformation * glm::vec4(rightFaceTranslation, 1.0f));

  glm::mat4 topFaceTransformation = glm::mat4(1.0f);
  topFaceTransformation = glm::rotate(topFaceTransformation, glm::radians(this->rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
  topFaceTransformation = glm::rotate(topFaceTransformation, glm::radians(this->rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
  topFaceTransformation = glm::rotate(topFaceTransformation, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
  topFaceTranslation = glm::vec3(topFaceTransformation * glm::vec4(topFaceTranslation, 1.0f));

  glm::mat4 bottomFaceTransformation = glm::mat4(1.0f);
  bottomFaceTransformation = glm::rotate(bottomFaceTransformation, glm::radians(this->rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
  bottomFaceTransformation = glm::rotate(bottomFaceTransformation, glm::radians(this->rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
  bottomFaceTransformation = glm::rotate(bottomFaceTransformation, glm::radians(this->rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
  bottomFaceTranslation = glm::vec3(bottomFaceTransformation * glm::vec4(bottomFaceTranslation, 1.0f));

  this->frontFace->translate(frontFaceTranslation + this->translation);
  this->frontFace->rotateX(this->rotationAngleX);
  this->frontFace->rotateY(this->rotationAngleY);
  this->frontFace->rotateZ(this->rotationAngleZ);
  this->frontFace->scale(this->scaling);

  this->backFace->translate(backFaceTranslation + this->translation);
  this->backFace->rotateX(this->rotationAngleX);
  this->backFace->rotateY(this->rotationAngleY);
  this->backFace->rotateZ(this->rotationAngleZ);
  this->backFace->scale(this->scaling);

  this->leftFace->translate(leftFaceTranslation + this->translation);
  this->leftFace->rotateX(this->rotationAngleX);
  this->leftFace->rotateY(this->rotationAngleY);
  this->leftFace->rotateZ(this->rotationAngleZ);
  this->leftFace->scale(this->scaling);

  this->rightFace->translate(rightFaceTranslation + this->translation);
  this->rightFace->rotateX(this->rotationAngleX);
  this->rightFace->rotateY(this->rotationAngleY);
  this->rightFace->rotateZ(this->rotationAngleZ);
  this->rightFace->scale(this->scaling);

  this->topFace->translate(topFaceTranslation + this->translation);
  this->topFace->rotateX(this->rotationAngleX);
  this->topFace->rotateY(this->rotationAngleY);
  this->topFace->rotateZ(this->rotationAngleZ);
  this->topFace->scale(this->scaling);

  this->bottomFace->translate(bottomFaceTranslation + this->translation);
  this->bottomFace->rotateX(this->rotationAngleX);
  this->bottomFace->rotateY(this->rotationAngleY);
  this->bottomFace->rotateZ(this->rotationAngleZ);
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
    this->bottomFace->setColor(color);
    return;
  }
}
