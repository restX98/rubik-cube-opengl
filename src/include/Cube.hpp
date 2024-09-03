#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Square.hpp"

enum class Face {
  FRONT_FACE,
  BACK_FACE,
  LEFT_FACE,
  RIGHT_FACE,
  TOP_FACE,
  BOTTOM_FACE
};

class Cube : public Model {
private:
  Square* frontFace;
  Square* backFace;
  Square* leftFace;
  Square* rightFace;
  Square* topFace;
  Square* bottomFace;

  float distanceToOrigin = 1.0f;

  void generateFaces();

public:
  Cube(Shader* shader);

  void draw(glm::mat4 model = glm::mat4(1.0f)) override;

  void setFaceColor(Face face, glm::vec3 color);

  void translate(float x, float y, float z) override;
  void rotateX(float angle, float force = 1.0f) override;
  void rotateY(float angle, float force = 1.0f) override;
  void rotateZ(float angle, float force = 1.0f) override;
  void scale(float scaling) override;

  void setPivot(float x, float y, float z);
};

#endif
