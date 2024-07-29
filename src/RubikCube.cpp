#include "RubikCube.hpp"

RubikCube::RubikCube(Shader* shader) : Model(shader) {
  generate(shader);
}

void RubikCube::generate(Shader* shader) {
  cubes.resize(3);
  for (int i = 0; i < 3; ++i) {
    cubes[i].resize(3);
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; k++) {
        cubes[i][j].push_back(Cube(shader));
      }
    }
  }

  this->transform();
}

void RubikCube::transform() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        glm::vec3 cubeTranslation = glm::vec3(0.0f, 0.0f, 0.0f);

        if (i == 0) {
          cubeTranslation.z = GAP;
          cubes[i][j][k].setFaceColor(Face::FRONT_FACE, RED);
        } else if (i == 2) {
          cubeTranslation.z = -GAP;
          cubes[i][j][k].setFaceColor(Face::BACK_FACE, ORANGE);
        }

        if (j == 0) {
          cubeTranslation.y = GAP;
          cubes[i][j][k].setFaceColor(Face::TOP_FACE, WHITE);
        } else if (j == 2) {
          cubeTranslation.y = -GAP;
          cubes[i][j][k].setFaceColor(Face::BOTTOM_FACE, YELLOW);
        }

        if (k == 0) {
          cubeTranslation.x = -GAP;
          cubes[i][j][k].setFaceColor(Face::LEFT_FACE, glm::vec3(GREEN));
        } else if (k == 2) {
          cubeTranslation.x = GAP;
          cubes[i][j][k].setFaceColor(Face::RIGHT_FACE, glm::vec3(BLUE));
        }

        cubes[i][j][k].translate(this->translation + cubeTranslation);
        cubes[i][j][k].rotate(this->rotationAngle, this->rotationAxis);
        cubes[i][j][k].scale(this->scaling);
      }
    }
  }
}

void RubikCube::draw(float delta) {
  this->transform();

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; k++) {
        cubes[i][j][k].draw();
      }
    }
  }
}
