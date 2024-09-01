#ifndef ANIMATED_MODEL_H
#define ANIMATED_MODEL_H

#include "Model.hpp"

#include <vector>

class AnimatedModel : public Model {
public:
  AnimatedModel(Shader* shader);
  ~AnimatedModel();

  virtual void draw(float deltaTime, glm::mat4 model = glm::mat4(1.0f)) = 0;
};

#endif
