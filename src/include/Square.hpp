#ifndef SQUARE_H
#define SQUARE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Model.hpp>
#include <Mesh.hpp>
#include <Shader.hpp>

enum class Plane {
  XY,
  XZ,
  YZ,
};

class Square : public Model {
private:
  Plane plane = Plane::XY;
  std::vector<Mesh> meshes;
  std::vector<Vertex> generateVertices(glm::vec3 color);

public:
  Square(Shader* shader, glm::vec3 color, Plane plane = Plane::XY);
  Square(Shader* shader, Plane plane = Plane::XY);

  void draw(float deltaTime = 0.0f) override;
  void setColor(glm::vec3 color);
};

#endif
