#include <AnimatedModel.hpp>

AnimatedModel::AnimatedModel(Shader* shader) : Model(shader) {}

AnimatedModel::~AnimatedModel() {
  delete position;
}
