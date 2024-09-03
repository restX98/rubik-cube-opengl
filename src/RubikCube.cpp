#include "RubikCube.hpp"

RubikCube::RubikCube(Shader* shader) : AnimatedModel(shader) {
  generate(shader);
}

void RubikCube::generate(Shader* shader) {
  cubes.resize(3);
  for (int i = 0; i < 3; i++) {
    cubes[i].resize(3);
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        cubes[i][j].push_back(new RubikCube::Cubby(shader, k - 1, j - 1, i - 1));
      }
    }
  }
}

void RubikCube::draw(glm::mat4 model) {
  glm::mat4 _model = model * this->position->getModel();

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        cubes[i][j][k]->draw(_model);
      }
    }
  }
}

void RubikCube::draw(float deltaTime, glm::mat4 model) {
  if (this->transition) {
    this->transition->update(deltaTime);
  }
  this->draw(model);
}


void RubikCube::translate(float x, float y, float z) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        cubes[i][j][k]->setPivot(x, y, z);
      }
    }
  }
  this->position->translate(x, y, z);
}

void RubikCube::rotateL(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, this->faceMapping[Face::LEFT_FACE], clockwise));
}

void RubikCube::rotateR(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, this->faceMapping[Face::RIGHT_FACE], clockwise));
}

void RubikCube::rotateF(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, this->faceMapping[Face::FRONT_FACE], clockwise));
}

void RubikCube::rotateB(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, this->faceMapping[Face::BACK_FACE], clockwise));
}

void RubikCube::rotateU(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, this->faceMapping[Face::TOP_FACE], clockwise));
}

void RubikCube::rotateD(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, this->faceMapping[Face::BOTTOM_FACE], clockwise));
}

void RubikCube::switchPOV(bool reverse) {
  delete this->transition;
  this->transition = nullptr;
  float angle = reverse ? 155.0f : 0.0f;
  this->setTransition(new RubikCube::POVTransition(this, this->position->getRotationAngleX(), angle));
}

void RubikCube::turnRight() {
  float currentRotation = this->position->getRotationAngleY();
  float angle = currentRotation - 90.0f;
  this->setTransition(new RubikCube::POVTransition(this, currentRotation, angle, Axis::Y));

  Face tmp = this->faceMapping[Face::FRONT_FACE];
  this->faceMapping[Face::FRONT_FACE] = this->faceMapping[Face::RIGHT_FACE];
  this->faceMapping[Face::RIGHT_FACE] = this->faceMapping[Face::BACK_FACE];
  this->faceMapping[Face::BACK_FACE] = this->faceMapping[Face::LEFT_FACE];
  this->faceMapping[Face::LEFT_FACE] = tmp;
}

void RubikCube::turnLeft() {
  float currentRotation = this->position->getRotationAngleY();
  float angle = currentRotation + 90.0f;
  this->setTransition(new RubikCube::POVTransition(this, currentRotation, angle, Axis::Y));

  Face tmp = this->faceMapping[Face::FRONT_FACE];
  this->faceMapping[Face::FRONT_FACE] = this->faceMapping[Face::LEFT_FACE];
  this->faceMapping[Face::LEFT_FACE] = this->faceMapping[Face::BACK_FACE];
  this->faceMapping[Face::BACK_FACE] = this->faceMapping[Face::RIGHT_FACE];
  this->faceMapping[Face::RIGHT_FACE] = tmp;
}

void RubikCube::turnUpsideDown() {
  float currentRotation = this->position->getRotationAngleZ();
  float angle = currentRotation + 180.0f;
  if (currentRotation >= 360.0f) {
    angle -= 360.0f;
  }
  this->setTransition(new RubikCube::POVTransition(this, currentRotation, angle, Axis::Z));

  Face tmp = this->faceMapping[Face::TOP_FACE];
  this->faceMapping[Face::TOP_FACE] = this->faceMapping[Face::BOTTOM_FACE];
  this->faceMapping[Face::BOTTOM_FACE] = tmp;
}

void RubikCube::Cubby::setPivot(float x, float y, float z) {
  FixedPosition* newPosix = new FixedPosition(*this->position, glm::vec3(x, y, z));

  delete this->position;
  this->position = newPosix;
}

void RubikCube::Cubby::updateAxis() {
  if (this->z == -1) {
    this->setZAxis(glm::vec3(0.0f, 0.0f, -1.0f));
  } else if (this->z == 1) {
    this->setZAxis(glm::vec3(0.0f, 0.0f, 1.0f));
  }

  if (this->y == -1) {
    this->setYAxis(glm::vec3(0.0f, -1.0f, 0.0f));
  } else if (this->y == 1) {
    this->setYAxis(glm::vec3(0.0f, 1.0f, 0.0f));
  }

  if (this->x == -1) {
    this->setXAxis(glm::vec3(1.0f, 0.0f, 0.0f));
  } else if (this->x == 1) {
    this->setXAxis(glm::vec3(-1.0f, 0.0f, 0.0f));
  }
}

RubikCube::Cubby::Cubby(Shader* shader, int x, int y, int z) : x(x), y(y), z(z), Cube(shader) {
  this->setPivot(0.0f, 0.0f, 0.0f);

  glm::vec3 cubeTranslation = glm::vec3(0.0f, 0.0f, 0.0f);

  if (x == -1) {
    cubeTranslation.x = -GAP;
    this->setFaceColor(Face::LEFT_FACE, glm::vec3(GREEN));
    this->setXAxis(glm::vec3(1.0f, 0.0f, 0.0f));
  } else if (x == 1) {
    cubeTranslation.x = GAP;
    this->setFaceColor(Face::RIGHT_FACE, glm::vec3(BLUE));
    this->setXAxis(glm::vec3(-1.0f, 0.0f, 0.0f));
  }

  if (y == -1) {
    cubeTranslation.y = GAP;
    this->setFaceColor(Face::TOP_FACE, WHITE);
    this->setYAxis(glm::vec3(0.0f, -1.0f, 0.0f));
  } else if (y == 1) {
    cubeTranslation.y = -GAP;
    this->setFaceColor(Face::BOTTOM_FACE, YELLOW);
    this->setYAxis(glm::vec3(0.0f, 1.0f, 0.0f));
  }

  if (z == -1) {
    cubeTranslation.z = GAP;
    this->setFaceColor(Face::FRONT_FACE, RED);
    this->setZAxis(glm::vec3(0.0f, 0.0f, -1.0f));
  } else if (z == 1) {
    cubeTranslation.z = -GAP;
    this->setFaceColor(Face::BACK_FACE, ORANGE);
    this->setZAxis(glm::vec3(0.0f, 0.0f, 1.0f));
  }

  this->translate(cubeTranslation.x, cubeTranslation.y, cubeTranslation.z);
}

RubikCube::FaceTransition::FaceTransition(RubikCube* rc, Face face, bool clockwise)
  : rubikCube(rc), sign(clockwise ? 1 : -1), angle(0.0f) {

  switch (face) {
  case Face::FRONT_FACE:
    this->axis = &RubikCube::Cubby::z;
    this->axisPos = -1;
    this->rotate = &Cube::rotateZ;
    this->faceNormal = glm::vec3(0.0f, 0.0f, -1.0f);
    break;
  case Face::BACK_FACE:
    this->axis = &RubikCube::Cubby::z;
    this->axisPos = 1;
    this->rotate = &Cube::rotateZ;
    this->faceNormal = glm::vec3(0.0f, 0.0f, 1.0f);
    break;
  case Face::LEFT_FACE:
    this->axis = &RubikCube::Cubby::x;
    this->axisPos = -1;
    this->rotate = &Cube::rotateX;
    this->faceNormal = glm::vec3(-1.0f, 0.0f, 0.0f);
    break;
  case Face::RIGHT_FACE:
    this->axis = &RubikCube::Cubby::x;
    this->axisPos = 1;
    this->rotate = &Cube::rotateX;
    this->faceNormal = glm::vec3(1.0f, 0.0f, 0.0f);
    break;
  case Face::TOP_FACE:
    this->axis = &RubikCube::Cubby::y;
    this->axisPos = -1;
    this->rotate = &Cube::rotateY;
    this->faceNormal = glm::vec3(0.0f, -1.0f, 0.0f);
    break;
  case Face::BOTTOM_FACE:
    this->axis = &RubikCube::Cubby::y;
    this->axisPos = 1;
    this->rotate = &Cube::rotateY;
    this->faceNormal = glm::vec3(0.0f, 1.0f, 0.0f);
    break;
  }
}

void RubikCube::FaceTransition::update(float deltaTime) {
  if (this->isEnded()) {
    return;
  }

  float deltaAngle = deltaTime * this->speed;
  this->angle += deltaAngle;
  if (this->angle >= 90.0f) {
    deltaAngle -= this->angle - 90.0f;
    this->end();
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        RubikCube::Cubby* c = this->rubikCube->cubes[i][j][k];
        if (c->*axis == axisPos) {
          (c->*rotate)(deltaAngle * this->sign, 1.0f);
        }
      }
    }
  }

  if (this->isEnded()) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          RubikCube::Cubby* c = this->rubikCube->cubes[i][j][k];
          if (c->*axis == axisPos) {
            // Could be encapsulated inside the Cubby class but I'm pissed off.
            glm::vec4 newPosition = glm::vec4(c->x, c->y, c->z, 1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f * this->sign), this->faceNormal);
            newPosition = glm::round(newPosition);
            c->x = newPosition.x;
            c->y = newPosition.y;
            c->z = newPosition.z;

            c->updateAxis();
          }
        }
      }
    }
  }
}

RubikCube::POVTransition::POVTransition(RubikCube* rc, float startingAngle, float endingAngle, Axis axis)
  : rubikCube(rc), angle(startingAngle), endingAngle(endingAngle), sign(startingAngle > endingAngle ? -1 : 1) {
  switch (axis) {
  case Axis::X:
    this->rotate = &RubikCube::rotateX;
    break;
  case Axis::Y:
    this->rotate = &RubikCube::rotateY;
    break;
  case Axis::Z:
    this->rotate = &RubikCube::rotateZ;
    break;
  }
}

void RubikCube::POVTransition::update(float deltaTime) {
  if (this->isEnded()) {
    return;
  }

  float deltaAngle = deltaTime * this->speed * this->sign;
  this->angle += deltaAngle;

  if (this->sign == -1) {
    if (this->angle <= this->endingAngle) {
      this->angle = this->endingAngle;
      this->end();
    }
  } else {
    if (this->angle >= this->endingAngle) {
      this->angle = this->endingAngle;
      this->end();
    }
  }

  (this->rubikCube->*rotate)(this->angle, 1.0f);
}
