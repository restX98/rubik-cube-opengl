#include <Square.hpp>

Square::Square(Shader* shader, glm::vec3 color, Plane plane) : Model(shader), plane(plane) {
  std::vector<Vertex> vertices = generateVertices(color);
  mesh = new Mesh(*shader, vertices, { 0, 1, 2, 2, 3, 0 });
  mesh->setup();
}

Square::Square(Shader* shader, Plane plane) : Square(shader, glm::vec3(0.0f, 0.0f, 0.0f), plane) {}

Square::~Square() {
  delete mesh;
}

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

void Square::draw(glm::mat4 model) {
  glm::mat4 _model = model * this->position->getModel();

  mesh->draw(_model);
}

void Square::setColor(glm::vec3 color) {
  this->mesh->updateVertices(generateVertices(color));
  this->mesh->setup();
}
