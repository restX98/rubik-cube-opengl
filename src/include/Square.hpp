#ifndef SQUARE_H
#define SQUARE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Mesh.hpp>
#include <Model.hpp>
#include <Position.hpp>
#include <Shader.hpp>

enum class Plane {
  XY,
  XZ,
  YZ,
};

class Square : public Model {
private:
  Mesh* mesh;
  Plane plane;

  std::vector<Vertex> generateVertices(glm::vec3 color);

public:
  Square(Shader* shader, glm::vec3 color, Plane plane = Plane::XY);
  Square(Shader* shader, Plane plane = Plane::XY);
  ~Square();

  void draw(glm::mat4 model = glm::mat4(1.0f)) override;
  void setColor(glm::vec3 color);
};

#endif
