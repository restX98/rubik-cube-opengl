#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>

#include "Event.hpp"
#include "Camera.hpp"

class Window {
protected:
  float currentFrame = 0;
  float lastFrame = 0;
  float deltaTime = 0;
  bool firstMouseMove = true;
  float lastX;
  float lastY;

  GLFWwindow* window;

public:
  Window(int width, int height, const char* title);
  ~Window();

  GLFWwindow* getWindow();

  void run(std::function<void(float)> renderFunction);

  void setKeyCallback(std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)> callback);
  void setCursorPosCallback(std::function<void(GLFWwindow* window_, double xPos_, double yPos_)> callback);
  void setFramebufferSizeCallback(std::function<void(GLFWwindow* window_, int width, int height)> callback);
  void setMouseButtonCallback(std::function<void(GLFWwindow* window, int button, int state, int mods)> callback);

private:
  Event<GLFWwindow*, int, int, int, int> keyEvent;
  Event<GLFWwindow*, double, double> cursorPosEvent;
  Event<GLFWwindow*, int, int, int> mouseButtonEvent;
  Event<GLFWwindow*, int, int> framebufferSizeEvent;

  bool shouldClose();
  void updateFrame();

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
  static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
  static void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods);
};

#endif
