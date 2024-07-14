#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

class Object {
protected:
  Shader& shader;
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

  glm::vec3 translation;
  float rotationAngle;
  glm::vec3 rotationAxis;
  glm::vec3 scaling;

public:
  Object(Shader& shader, float* vertices, int size);
  ~Object();

  void draw();

  void translate();
  void translate(glm::vec3 translation);
  void rotate();
  void rotate(float angle, glm::vec3 axis);
  void scale();
  void scale(glm::vec3 scaling);

private:
  void transform();
  void resetTransformation();
};

#endif
