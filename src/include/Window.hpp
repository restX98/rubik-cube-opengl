#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
protected:
  GLFWwindow* window;

public:
  Window(int width, int height, const char* title);
  ~Window();

  GLFWwindow* getWindow();

  void run(std::function<void()> renderFunction);

private:
  bool shouldClose();
  void updateFrame();
};

#endif
