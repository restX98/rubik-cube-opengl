#ifndef ANIMATED_MODEL_H
#define ANIMATED_MODEL_H

#include <vector>

#include "Model.hpp"

class AnimatedModel : public Model {
public:
  AnimatedModel(Shader* shader);
  ~AnimatedModel();

  virtual void draw(float deltaTime, glm::mat4 model = glm::mat4(1.0f)) = 0;

protected:
  class Transition {
  public:
    Transition();
    virtual ~Transition() = default;
    virtual void update(float deltaTime) = 0;

    bool isEnded();
    void end();

  private:
    bool ended;
  };

  Transition* transition;

  void setTransition(Transition* transition);
};

#endif
