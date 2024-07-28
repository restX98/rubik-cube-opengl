#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.hpp"

#include <vector>

class Model {
protected:
  Shader* shader;

  std::vector<Mesh> meshes;

private:
  glm::vec3 translation;
  float rotationAngle;
  glm::vec3 rotationAxis;
  glm::vec3 scaling;

  void transform();
  void resetTransformation();

public:
  Model(Shader* shader);

  void draw();

  void translate();
  void translate(glm::vec3 translation);
  void rotate();
  void rotate(float angle, glm::vec3 axis);
  void scale();
  void scale(glm::vec3 scaling);
};

#endif
