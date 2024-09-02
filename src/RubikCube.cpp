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
        Cube* cube = new Cube(shader);
        cube->setPivot(0.0f, 0.0f, 0.0f);

        glm::vec3 cubeTranslation = glm::vec3(0.0f, 0.0f, 0.0f);

        if (i == 0) {
          cubeTranslation.z = GAP;
          cube->setFaceColor(Face::FRONT_FACE, RED);
          cube->setZAxis(glm::vec3(0.0f, 0.0f, -1.0f));
        } else if (i == 2) {
          cubeTranslation.z = -GAP;
          cube->setFaceColor(Face::BACK_FACE, ORANGE);
          cube->setZAxis(glm::vec3(0.0f, 0.0f, 1.0f));
        }

        if (j == 0) {
          cubeTranslation.y = GAP;
          cube->setFaceColor(Face::TOP_FACE, WHITE);
          cube->setYAxis(glm::vec3(0.0f, -1.0f, 0.0f));
        } else if (j == 2) {
          cubeTranslation.y = -GAP;
          cube->setFaceColor(Face::BOTTOM_FACE, YELLOW);
          cube->setYAxis(glm::vec3(0.0f, 1.0f, 0.0f));
        }

        if (k == 0) {
          cubeTranslation.x = -GAP;
          cube->setFaceColor(Face::LEFT_FACE, glm::vec3(GREEN));
          cube->setXAxis(glm::vec3(1.0f, 0.0f, 0.0f));
        } else if (k == 2) {
          cubeTranslation.x = GAP;
          cube->setFaceColor(Face::RIGHT_FACE, glm::vec3(BLUE));
          cube->setXAxis(glm::vec3(-1.0f, 0.0f, 0.0f));
        }

        cube->translate(cubeTranslation.x, cubeTranslation.y, cubeTranslation.z);

        cubes[i][j].push_back(new CubePosition({ cube, k - 1, j - 1, i - 1 }));
      }
    }
  }
}

void RubikCube::draw(glm::mat4 model) {
  glm::mat4 _model = model * this->position->getModel();

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        cubes[i][j][k]->cube->draw(_model);
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
        cubes[i][j][k]->cube->setPivot(x, y, z);
      }
    }
  }
  this->position->translate(x, y, z);
}

void RubikCube::rotateX(float angle, float force) {
  this->position->rotateX(angle, force);
}

void RubikCube::rotateY(float angle, float force) {
  this->position->rotateY(angle, force);
}

void RubikCube::rotateZ(float angle, float force) {
  this->position->rotateZ(angle, force);
}

void RubikCube::scale(float scaling) {
  this->position->scale(scaling);
}

void RubikCube::rotateL(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, Face::LEFT_FACE, clockwise));
}

void RubikCube::rotateR(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, Face::RIGHT_FACE, clockwise));
}

void RubikCube::rotateF(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, Face::FRONT_FACE, clockwise));
}

void RubikCube::rotateB(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, Face::BACK_FACE, clockwise));
}

void RubikCube::rotateU(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, Face::TOP_FACE, clockwise));
}

void RubikCube::rotateD(bool clockwise) {
  this->setTransition(new RubikCube::FaceTransition(this, Face::BOTTOM_FACE, clockwise));
}

void RubikCube::setTransition(Transition* transition) {
  if (!this->transition) {
    this->transition = transition;
  } else if (this->transition->isEnded()) {
    delete this->transition;
    this->transition = transition;
  }
}

void RubikCube::updateAxis(CubePosition* c) {
  if (c->z == -1) {
    c->cube->setZAxis(glm::vec3(0.0f, 0.0f, -1.0f));
  } else if (c->z == 1) {
    c->cube->setZAxis(glm::vec3(0.0f, 0.0f, 1.0f));
  }

  if (c->y == -1) {
    c->cube->setYAxis(glm::vec3(0.0f, -1.0f, 0.0f));
  } else if (c->y == 1) {
    c->cube->setYAxis(glm::vec3(0.0f, 1.0f, 0.0f));
  }

  if (c->x == -1) {
    c->cube->setXAxis(glm::vec3(1.0f, 0.0f, 0.0f));
  } else if (c->x == 1) {
    c->cube->setXAxis(glm::vec3(-1.0f, 0.0f, 0.0f));
  }
}

RubikCube::FaceTransition::FaceTransition(RubikCube* rc, Face face, bool clockwise)
  : rubikCube(rc), clockwise(clockwise), angle(0.0f) {

  switch (face) {
  case Face::FRONT_FACE:
    this->axis = &CubePosition::z;
    this->axisPos = -1;
    this->rotate = &Cube::rotateZ;
    this->faceNormal = glm::vec3(0.0f, 0.0f, -1.0f);
    break;
  case Face::BACK_FACE:
    this->axis = &CubePosition::z;
    this->axisPos = 1;
    this->rotate = &Cube::rotateZ;
    this->faceNormal = glm::vec3(0.0f, 0.0f, 1.0f);
    break;
  case Face::LEFT_FACE:
    this->axis = &CubePosition::x;
    this->axisPos = -1;
    this->rotate = &Cube::rotateX;
    this->faceNormal = glm::vec3(-1.0f, 0.0f, 0.0f);
    break;
  case Face::RIGHT_FACE:
    this->axis = &CubePosition::x;
    this->axisPos = 1;
    this->rotate = &Cube::rotateX;
    this->faceNormal = glm::vec3(1.0f, 0.0f, 0.0f);
    break;
  case Face::TOP_FACE:
    this->axis = &CubePosition::y;
    this->axisPos = -1;
    this->rotate = &Cube::rotateY;
    this->faceNormal = glm::vec3(0.0f, -1.0f, 0.0f);
    break;
  case Face::BOTTOM_FACE:
    this->axis = &CubePosition::y;
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

  int sign = this->clockwise ? 1 : -1;

  float deltaAngle = deltaTime * this->speed;
  this->angle += deltaAngle;
  if (this->angle >= 90.0f) {
    deltaAngle -= this->angle - 90.0f;
    this->end();
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        CubePosition* c = this->rubikCube->cubes[i][j][k];
        if (c->*axis == axisPos) {
          (c->cube->*rotate)(deltaAngle * sign, 1.0f);
        }
      }
    }
  }

  if (this->isEnded()) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          CubePosition* c = this->rubikCube->cubes[i][j][k];
          if (c->*axis == axisPos) {
            glm::vec4 newPosition = glm::vec4(c->x, c->y, c->z, 1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f * sign), this->faceNormal);
            newPosition = glm::round(newPosition);
            c->x = newPosition.x;
            c->y = newPosition.y;
            c->z = newPosition.z;
            this->rubikCube->updateAxis(c);
          }
        }
      }
    }
  }
}
