#include <Square.hpp>

Square::Square(Shader* shader, glm::vec3 color) : Model(shader) {
  std::vector<Vertex> vertices = generateVertices(color);
  Mesh m(*shader, vertices, { 0, 1, 2, 2, 3, 0 });
  this->meshes.push_back(m);

  for (int i = 0; i < meshes.size(); i++) {
    meshes[i].setup();
  }
}

Square::Square(Shader* shader) : Square(shader, glm::vec3(0.0f, 0.0f, 0.0f)) {}

std::vector<Vertex> Square::generateVertices(glm::vec3 color) {
  std::vector<Vertex> frontFaceVertices;
  frontFaceVertices.push_back(Vertex({ glm::vec3(-0.5f, -0.5f, 0.0f), color }));  // Bottom-left
  frontFaceVertices.push_back(Vertex({ glm::vec3(0.5f, -0.5f, 0.0f), color }));   // Bottom-right
  frontFaceVertices.push_back(Vertex({ glm::vec3(0.5f, 0.5f, 0.0f), color }));    // Top-right
  frontFaceVertices.push_back(Vertex({ glm::vec3(-0.5f, 0.5f, 0.0f), color }));   // Top-left

  return frontFaceVertices;
}

void Square::draw() {
  this->transform();

  for (int i = 0; i < meshes.size(); i++) {
    meshes[i].draw();
  }
}

void Square::setColor(glm::vec3 color) {
  this->meshes[0].updateVertices(generateVertices(color));
  this->meshes[0].setup();
}
