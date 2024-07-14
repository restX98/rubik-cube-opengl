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
    std::cerr << "ERROR:WINDOW::GLFW_CREATE_WINDOW_FAILED" << std::endl;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);

  glfwSetWindowUserPointer(window, this);

  this->lastX = width / 2;
  this->lastY = height / 2;
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

  this->currentFrame = glfwGetTime();
  this->deltaTime = this->currentFrame - this->lastFrame;
  this->lastFrame = this->currentFrame;
}

GLFWwindow* Window::getWindow() {
  return this->window;
}

void Window::run(std::function<void()> renderFunction) {
  while (!shouldClose()) {
    this->processInput();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->camera->update();

    renderFunction();

    this->updateFrame();
  }
}

void Window::setCamera(Camera* camera) {
  this->camera = camera;

  glfwSetCursorPosCallback(window, Window::cursorPositionCallback);
}

void Window::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    this->camera->moveForward(this->deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    this->camera->moveBackward(this->deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    this->camera->moveLeft(this->deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    this->camera->moveRight(this->deltaTime);
  }
}

void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
  Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->updateCursorPosition(xpos, ypos);
  }
}

void Window::updateCursorPosition(double xpos, double ypos) {
  if (this->firstMouseMove) {
    this->lastX = xpos;
    this->lastY = ypos;
    this->firstMouseMove = false;
  }

  float xOffset = xpos - this->lastX;
  float yOffset = this->lastY - ypos; // reversed since y-coordinates range from bottom to top
  this->lastX = xpos;
  this->lastY = ypos;

  this->camera->lookAround(xOffset, yOffset);
}
