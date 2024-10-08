#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Shader.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Color;
};

class Mesh {
private:
  Shader& shader;
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indexes;

public:
  Mesh(Shader& shader, std::vector<Vertex> vertices, std::vector<unsigned int> indexes);
  ~Mesh();

  void updateVertices(std::vector<Vertex> vertices);
  void setup();
  void draw(glm::mat4 model = glm::mat4(1.0f));
};


#endif
