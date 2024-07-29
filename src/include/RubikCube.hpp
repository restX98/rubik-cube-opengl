#ifndef RUBIK_CUBE_H
#define RUBIK_CUBE_H

#include <Model.hpp>
#include <Shader.hpp>
#include <Cube.hpp>

#include <vector>

#define GAP 1.05f

#define GREEN glm::vec3(0.0f, 0.6078f, 0.2823f)
#define WHITE glm::vec3(1.0f, 1.0f, 1.0f)
#define RED glm::vec3(0.7176f, 0.0705f, 0.2039f)
#define YELLOW glm::vec3(1.0f, 0.8352f, 0.0f)
#define BLUE glm::vec3(0.0f, 0.2745f, 0.6784f)
#define ORANGE glm::vec3(1.0f, 0.3451f, 0.0f)

class RubikCube : public Model {
private:
  std::vector<std::vector<std::vector<Cube>>> cubes;
  void generate(Shader* shader);
  void align();

public:
  RubikCube(Shader* shader);

  void draw(float delta);
  void transform();
};

#endif
