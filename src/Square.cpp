#include <Square.hpp>

Square::Square(Shader* shader, glm::vec3 color) : Model(shader) {
  std::vector<unsigned int> indexes = { 0, 1, 2, 2, 3, 0 };
  glm::vec3 black = glm::vec3(0.0f, 0.0f, 0.0f);
  std::vector<Vertex> vertices = generateVertices(black);
  Mesh m(*shader, vertices, indexes);
  this->meshes.push_back(m);

  for (int i = 0; i < meshes.size(); i++) {
    meshes[i].setup();
  }
}

Square::Square(Shader* shader) : Square(shader, glm::vec3(0.0f, 0.0f, 0.0f)) {}

std::vector<Vertex> Square::generateVertices(glm::vec3 color) {
  std::vector<Vertex> frontFaceVertices;
  frontFaceVertices.push_back(Vertex({ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f) }));  // Bottom-left
  frontFaceVertices.push_back(Vertex({ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f) }));   // Bottom-right
  frontFaceVertices.push_back(Vertex({ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f) }));    // Top-right
  frontFaceVertices.push_back(Vertex({ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f) }));   // Top-left

  return frontFaceVertices;
}
