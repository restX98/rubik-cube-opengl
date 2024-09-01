#include "RubikCube.hpp"

#include <iostream>

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
  if (this->isTransitionR) {
    float deltaAngle = deltaTime * this->rotationSpeed;
    this->rotationAngle += deltaAngle;
    if (this->rotationAngle >= 90.0f) {
      deltaAngle -= this->rotationAngle - 90.0f;
      this->rotationAngle = 90.0f;
      this->isTransitionR = false;
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          CubePosition* c = this->cubes[i][j][k];
          if (c->x == 1) {
            c->cube->rotateX(deltaAngle);
          }
        }
      }
    }

    if (!this->isTransitionR) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 3; k++) {
            CubePosition* c = this->cubes[i][j][k];
            if (c->x == 1) {
              glm::vec4 newPosition = glm::vec4(c->x, c->y, c->z, 1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
              newPosition = glm::round(newPosition);
              c->x = newPosition.x;
              c->y = newPosition.y;
              c->z = newPosition.z;
              this->updateAxis(c);
            }
          }
        }
      }
    }
  }

  if (this->isTransitionL) {
    float deltaAngle = deltaTime * this->rotationSpeed;
    this->rotationAngle -= deltaAngle;
    if (this->rotationAngle <= -90.0f) {
      deltaAngle += this->rotationAngle + 90.0f;
      this->rotationAngle = 90.0f;
      this->isTransitionL = false;
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          CubePosition* c = this->cubes[i][j][k];
          if (c->x == -1) {
            c->cube->rotateX(deltaAngle);
          }
        }
      }
    }

    if (!this->isTransitionL) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 3; k++) {
            CubePosition* c = this->cubes[i][j][k];
            if (c->x == -1) {
              glm::vec4 newPosition = glm::vec4(c->x, c->y, c->z, 1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
              newPosition = glm::round(newPosition);
              c->x = newPosition.x;
              c->y = newPosition.y;
              c->z = newPosition.z;
              this->updateAxis(c);
            }
          }
        }
      }
    }
  }

  if (this->isTransitionF) {
    float deltaAngle = deltaTime * this->rotationSpeed;
    this->rotationAngle += deltaAngle;
    if (this->rotationAngle >= 90.0f) {
      deltaAngle -= this->rotationAngle - 90.0f;
      this->rotationAngle = 90.0f;
      this->isTransitionF = false;
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          CubePosition* c = this->cubes[i][j][k];
          if (c->z == -1) {
            c->cube->rotateZ(deltaAngle);
          }
        }
      }
    }

    if (!this->isTransitionF) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 3; k++) {
            CubePosition* c = this->cubes[i][j][k];
            if (c->z == -1) {
              glm::vec4 newPosition = glm::vec4(c->x, c->y, c->z, 1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
              newPosition = glm::round(newPosition);
              c->x = newPosition.x;
              c->y = newPosition.y;
              c->z = newPosition.z;
              this->updateAxis(c);
            }
          }
        }
      }
    }
  }


  if (this->isTransitionU) {
    float deltaAngle = deltaTime * this->rotationSpeed;
    this->rotationAngle += deltaAngle;
    if (this->rotationAngle >= 90.0f) {
      deltaAngle -= this->rotationAngle - 90.0f;
      this->rotationAngle = 90.0f;
      this->isTransitionU = false;
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          CubePosition* c = this->cubes[i][j][k];
          if (c->y == -1) {
            c->cube->rotateY(deltaAngle);
          }
        }
      }
    }

    if (!this->isTransitionU) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 3; k++) {
            CubePosition* c = this->cubes[i][j][k];
            if (c->y == -1) {
              glm::vec4 newPosition = glm::vec4(c->x, c->y, c->z, 1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
              newPosition = glm::round(newPosition);
              c->x = newPosition.x;
              c->y = newPosition.y;
              c->z = newPosition.z;
              this->updateAxis(c);
            }
          }
        }
      }
    }
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

void RubikCube::rotateL() {
  if (!this->isTransitionL) {
    std::cout << "L pressed" << std::endl;
    this->isTransitionL = true;
    this->rotationAngle = 0;
  }
}

void RubikCube::rotateR() {
  if (!this->isTransitionR) {
    std::cout << "R pressed" << std::endl;
    this->isTransitionR = true;
    this->rotationAngle = 0;
  }
}

void RubikCube::rotateF() {
  if (!this->isTransitionF) {
    std::cout << "F pressed" << std::endl;
    this->isTransitionF = true;
    this->rotationAngle = 0;
  }
}

void RubikCube::rotateU() {
  if (!this->isTransitionU) {
    std::cout << "U pressed" << std::endl;
    this->isTransitionU = true;
    this->rotationAngle = 0;
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


void RubikCube::draw(float deltaTime) {
  this->transform();

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; k++) {
        cubes[i][j][k].draw();
      }
    }
  }
}
