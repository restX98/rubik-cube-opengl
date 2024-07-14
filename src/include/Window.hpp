#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.hpp"

class Window {
protected:
  float currentFrame = 0;
  float lastFrame = 0;
  float deltaTime = 0;

  GLFWwindow* window;
  Camera* camera;

public:
  Window(int width, int height, const char* title);
  ~Window();

  GLFWwindow* getWindow();

  void run(std::function<void()> renderFunction);

  void setCamera(Camera* camera);

private:
  bool shouldClose();
  void updateFrame();
  void processInput();

};

#endif
