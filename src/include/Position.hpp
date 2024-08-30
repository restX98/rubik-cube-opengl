#ifndef POSITION_H
#define POSITION_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Position {
private:
  void resetTransformation();

protected:
  glm::mat4 model = glm::mat4(1.0f);
  glm::vec3 translation;
  float rotationAngleX;
  float rotationForceX;
  float rotationAngleY;
  float rotationForceY;
  float rotationAngleZ;
  float rotationForceZ;
  float scaling;

  bool isDirty = true;

public:
  Position();

  virtual glm::mat4 getModel();

  virtual void translate();
  virtual void translate(float x, float y, float z);
  virtual void resetRotation();
  virtual void rotateX(float angle, float force = 1.0f);
  virtual void rotateY(float angle, float force = 1.0f);
  virtual void rotateZ(float angle, float force = 1.0f);
  virtual void scale();
  virtual void scale(float scaling);
};

#endif
