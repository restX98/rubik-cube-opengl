#include <glad/glad.h>

#include <iostream>
#include "Window.hpp"
#include "Shader.hpp"
#include "Object.hpp"
#include "constants.hpp"

int main() {

  Window window(
    Constants::Graphics::WINDOW_WIDTH,
    Constants::Graphics::WINDOW_HEIGHT,
    Constants::APP_NAME
  );
  if (window.getWindow() == nullptr) {
    std::cout << "ERROR::MAIN::EMPTY_WINDOW" << std::endl;
    return -1;
  }

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "ERROR::MAIN::GLAD_INIT_FAILED" << std::endl;
    return -1;
  }

  Shader shader(SHADERS_PATH "shader.vert", SHADERS_PATH "shader.frag");

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left vertex
    0.5f, -0.5f, 0.0f, // right vertex
    0.0f, 0.5f, 0.0f, // top vertex
  };

  Object triangle(vertices, sizeof(vertices));

  window.run(
    [&shader, &triangle]() {
      shader.use();
      triangle.draw();
    }
  );

  return 0;
}
