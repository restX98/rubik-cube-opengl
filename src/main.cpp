#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Window.hpp"
#include "constants.hpp"

int main() {

  Window window = Window(
    Constants::Graphics::WINDOW_WIDTH,
    Constants::Graphics::WINDOW_HEIGHT,
    Constants::APP_NAME
  );

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  while (!window.shouldClose()) {


    window.updateFrame();
  }

  glfwTerminate();
  return 0;
}
