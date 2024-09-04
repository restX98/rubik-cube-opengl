#include "Window.hpp"

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

void Window::run(std::function<void(float)> renderFunction) {
  glEnable(GL_DEPTH_TEST);

  while (!shouldClose()) {
    glClearColor(this->background.x, this->background.y, this->background.z, this->background.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderFunction(this->deltaTime);

    this->updateFrame();
  }
}

void Window::setBackgroundColor(float red, float green, float blue, float alpha) {
  this->background = glm::vec4(red, green, blue, alpha);
}

void Window::setKeyCallback(std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)> callback) {
  this->keyEvent.setCallback(callback);
  glfwSetKeyCallback(this->window, this->keyCallback);
}

void Window::setCursorPosCallback(std::function<void(GLFWwindow* window, double xPos, double yPos)> callback) {
  this->cursorPosEvent.setCallback(callback);
  glfwSetCursorPosCallback(this->window, this->cursorPosCallback);
}

void Window::setFramebufferSizeCallback(std::function<void(GLFWwindow* window, int width, int height)> callback) {
  this->framebufferSizeEvent.setCallback(
    [callback](GLFWwindow* window, int width, int height) {
      (callback)(window, width, height);
      glViewport(0, 0, width, height);
    }
  );
  glfwSetFramebufferSizeCallback(this->window, this->framebufferSizeCallback);
}

void Window::setMouseButtonCallback(std::function<void(GLFWwindow* window, int button, int state, int mods)> callback) {
  this->mouseButtonEvent.setCallback(callback);
  glfwSetMouseButtonCallback(this->window, this->mouseButtonCallback);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->keyEvent(window, key, scancode, action, mods);
  }
}

void Window::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
  Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->cursorPosEvent(window, xPos, yPos);
  }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->framebufferSizeEvent(window, width, height);
  }
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int state, int mods) {
  Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->mouseButtonEvent(window, button, state, mods);
  }
}
