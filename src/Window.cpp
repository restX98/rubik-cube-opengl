#include "Window.hpp"

#include <iostream>

Window::Window(int width, int height, const char* title) : window(nullptr) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (this->window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);
}

Window::~Window() {
  if (this->window != nullptr) {
    glfwDestroyWindow(this->window);
  }
  glfwTerminate();
}

bool Window::shouldClose() {
  return glfwWindowShouldClose(this->window);
}

void Window::updateFrame() {
  glfwSwapBuffers(this->window);
  glfwPollEvents();
}
