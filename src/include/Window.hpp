#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h> // Included here because all the possible Window.cpp definition should use GLFW

class Window {
protected:
  GLFWwindow* window;

public:
  Window(int width, int height, const char* title);
  ~Window();

  bool shouldClose();

  void updateFrame();
};

#endif
