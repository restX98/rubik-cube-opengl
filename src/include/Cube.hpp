#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Model.hpp>
#include <Shader.hpp>
#include <Square.hpp>

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
  void relativeTransform(Square* face, glm::vec3 relativeTranslation);

public:
  Cube(Shader* shader);

  void draw();
  void transform();

  void setFaceColor(Face face, glm::vec3 color);
};

#endif
