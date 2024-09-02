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
  Camera* camera;

public:
  Window(int width, int height, const char* title);
  ~Window();

  GLFWwindow* getWindow();

  void run(std::function<void(float)> renderFunction);

  void setCamera(Camera* camera);
  void setKeyCallback(std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)> callback);

private:
  Event<GLFWwindow*, int, int, int, int> keyEvent;
  // Event<Window&, MouseButton, MouseButtonState, ModifierKeyBit> mouseButtonEvent;
  // Event<Window&, double, double> cursorPosEvent;

  bool shouldClose();
  void updateFrame();

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
  void updateCursorPosition(double xpos, double ypos);
};

#endif
