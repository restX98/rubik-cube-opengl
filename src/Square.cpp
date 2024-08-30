#include <Square.hpp>

Square::Square(Shader* shader, glm::vec3 color, Plane plane) : Model(shader), plane(plane) {
  std::vector<Vertex> vertices = generateVertices(color);
  Mesh m(*shader, vertices, { 0, 1, 2, 2, 3, 0 });
  this->meshes.push_back(m);

  for (int i = 0; i < meshes.size(); i++) {
    meshes[i].setup();
  }
}

Square::Square(Shader* shader, Plane plane) : Square(shader, glm::vec3(0.0f, 0.0f, 0.0f), plane) {}

std::vector<Vertex> Square::generateVertices(glm::vec3 color) {
  std::vector<Vertex> vertices;
  switch (this->plane) {
  default:
  case Plane::XY:
    vertices.push_back(Vertex({ glm::vec3(-1.0f, -1.0f, 0.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(1.0f, -1.0f, 0.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(1.0f, 1.0f, 0.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(-1.0f, 1.0f, 0.0f), color }));
    break;
  case Plane::XZ:
    vertices.push_back(Vertex({ glm::vec3(-1.0f, 0.0f, -1.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(1.0f, 0.0f, -1.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(1.0f, 0.0f, 1.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(-1.0f, 0.0f, 1.0f), color }));
    break;
  case Plane::YZ:
    vertices.push_back(Vertex({ glm::vec3(0.0f,-1.0f, -1.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(0.0f, 1.0f, -1.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(0.0f, 1.0f, 1.0f), color }));
    vertices.push_back(Vertex({ glm::vec3(0.0f,-1.0f, 1.0f), color }));
    break;
  }
  return vertices;
}

void Square::draw(float deltaTime) {
  this->transform();

  for (int i = 0; i < meshes.size(); i++) {
    meshes[i].draw();
  }
}

void Square::setColor(glm::vec3 color) {
  this->meshes[0].updateVertices(generateVertices(color));
  this->meshes[0].setup();
}
