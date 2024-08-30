#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.hpp"

#include <vector>

class Model {
private:
  glm::mat4 model = glm::mat4(1.0f);

protected:
  Shader* shader;

  glm::vec3 translation;
  float rotationAngleX;
  float rotationForceX;
  float rotationAngleY;
  float rotationForceY;
  float rotationAngleZ;
  float rotationForceZ;
  float scaling;

  bool isDirty = true;

  void transform();

private:
  void resetTransformation();

public:
  Model(Shader* shader);

  virtual void draw(float deltaTime = 0.0f);

  void translate();
  void translate(glm::vec3 translation);
  void resetRotation();
  void rotateX(float angle, float force = 1.0f);
  void rotateY(float angle, float force = 1.0f);
  void rotateZ(float angle, float force = 1.0f);
  void scale();
  void scale(float scaling);
};

#endif
