#include <AnimatedModel.hpp>

AnimatedModel::AnimatedModel(Shader* shader) : transition(nullptr), Model(shader) {}

AnimatedModel::~AnimatedModel() {
  delete position;
}

AnimatedModel::Transition::Transition() : ended(false) {}

bool AnimatedModel::Transition::isEnded() {
  return this->ended;
}

void AnimatedModel::Transition::end() {
  this->ended = true;
}

void AnimatedModel::setTransition(Transition* transition) {
  if (!this->transition) {
    this->transition = transition;
  } else if (this->transition->isEnded()) {
    delete this->transition;
    this->transition = transition;
  }
}
