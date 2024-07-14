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
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;
  float speed = 2.5f;

public:
  Camera(Shader& shader);

  void moveForward(float delta = 1);
  void moveBackward(float delta = 1);
  void moveLeft(float delta = 1);
  void moveRight(float delta = 1);

  void update();
};
#endif
