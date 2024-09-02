#ifndef FIXED_POSITION_H
#define FIXED_POSITION_H

#include "Position.hpp"

class FixedPosition : public Position {
protected:
  glm::vec3 pivot;

public:
  FixedPosition(glm::vec3 pivot = glm::vec3(0.0f));
  FixedPosition(Position position, glm::vec3 pivot);

  glm::mat4 getModel() override;

  void translate(float x, float y, float z) override;
  void rotateX(float angle, float force = 1.0f) override;
  void rotateY(float angle, float force = 1.0f) override;
  void rotateZ(float angle, float force = 1.0f) override;
};

#endif
