#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.hpp"
#include "Position.hpp"
#include "RelativePosition.hpp"
#include "FixedPosition.hpp"

#include <vector>

class Model {
private:
  glm::mat4 model = glm::mat4(1.0f);

protected:
  Shader* shader;
  Position* position;

  bool isDirty = true;

public:
  Model(Shader* shader);

  virtual void draw(glm::mat4 model = glm::mat4(1.0f)) = 0;
  void setPivot(float x, float y, float z);
  void removePivot();

  virtual void translate(float x, float y, float z);
  virtual void rotateX(float angle, float force = 1.0f);
  virtual void rotateY(float angle, float force = 1.0f);
  virtual void rotateZ(float angle, float force = 1.0f);
  virtual void scale(float scaling);

  virtual void setXAxis(glm::vec3 axis);
  virtual void setYAxis(glm::vec3 axis);
  virtual void setZAxis(glm::vec3 axis);
};

#endif
