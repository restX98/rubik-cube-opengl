#include <glad/glad.h>

#include <iostream>
#include <vector>
#include "Window.hpp"
#include "Shader.hpp"
#include "RubikCube.hpp"
#include "Camera.hpp"
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

  Camera camera(shader);
  window.setCamera(&camera);

  RubikCube rb(&shader);

  rb.translate(glm::vec3(0.0f, 0.0f, -5.0f));

  window.run(
    [&shader, &rb](float deltaTime) {
      shader.use();
      std::cout << deltaTime << "\n";

      rb.draw(deltaTime);
    }
  );

  return 0;
}
