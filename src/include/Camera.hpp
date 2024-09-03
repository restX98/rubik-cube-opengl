#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

class Camera {
protected:
  Shader& shader;
  glm::mat4 view;
  glm::mat4 projection;

  glm::vec3 cameraInitialPos;
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;

  float width;
  float height;

public:
  Camera(Shader& shader, float width, float height);

  void lookAround(float xPos, float yPos);
  void update();

  void setHeight(int height);
  void setWidth(int width);
};
#endif
