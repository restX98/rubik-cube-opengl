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

  glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
  glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

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

  virtual void setXAxis(glm::vec3 axis);
  virtual void setYAxis(glm::vec3 axis);
  virtual void setZAxis(glm::vec3 axis);

  virtual glm::vec3 getXAxis();
  virtual glm::vec3 getYAxis();
  virtual glm::vec3 getZAxis();
};

#endif
