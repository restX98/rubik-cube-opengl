#ifndef RELATIVE_POSITION_H
#define RELATIVE_POSITION_H

#include "Position.hpp"

class RelativePosition : public Position {

protected:
  glm::vec3 pivot;

public:
  RelativePosition(glm::vec3 pivot = glm::vec3(0.0f));
  RelativePosition(Position position, glm::vec3 pivot);

  glm::mat4 getModel() override;

  void rotateX(float angle, float force = 1.0f) override;
  void rotateY(float angle, float force = 1.0f) override;
  void rotateZ(float angle, float force = 1.0f) override;
};

#endif
