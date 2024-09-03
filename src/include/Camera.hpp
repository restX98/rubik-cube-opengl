#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#include "Shader.hpp"

class Camera {
public:
  enum class State {
    NORMAL,
    REVERSE
  };

protected:
  Shader& shader;
  glm::mat4 view;
  glm::mat4 projection;

  glm::vec3 cameraInitialPos;
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;

public:
  Camera(Shader& shader, int width, int height);

  void update();

  void setWindowSize(int width, int height);
  void setMouseCoords(int xPos, int yPos);

private:
  int width;
  int height;
  int xPos;
  int yPos;

  void lookAround();
};
#endif
