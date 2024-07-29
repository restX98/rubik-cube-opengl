#ifndef SQUARE_H
#define SQUARE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Model.hpp>
#include <Mesh.hpp>
#include <Shader.hpp>

class Square : public Model {
private:
  std::vector<Mesh> meshes;
  std::vector<Vertex> generateVertices(glm::vec3 color);

public:
  Square(Shader* shader, glm::vec3 color);
  Square(Shader* shader);

  void draw();
  void setColor(glm::vec3 color);
};

#endif
