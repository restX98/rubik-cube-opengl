#include <glad/glad.h>

#include <iostream>
#include <vector>
#include "Window.hpp"
#include "Shader.hpp"
#include "RubikCube.hpp"
#include "Cube.hpp"
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

  Camera camera(shader, Constants::Graphics::WINDOW_WIDTH, Constants::Graphics::WINDOW_HEIGHT);

  RubikCube rubikCube(&shader);

  window.setFramebufferSizeCallback(
    [&camera](GLFWwindow* window, int width, int height) {
      std::cout << "W: " << width << " H: " << height << std::endl;
      camera.setWidth(width);
      camera.setHeight(height);
    }
  );

  window.setCursorPosCallback(
    [&camera](GLFWwindow* window, double xPos, double yPos) {
      camera.lookAround(xPos, yPos);
    }
  );

  window.setKeyCallback(
    [&camera, &rubikCube](GLFWwindow* window, int key, int scancode, int action, int mods) {
      if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
      }

      bool clockwise = !(mods & GLFW_MOD_SHIFT);
      if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        rubikCube.rotateL(clockwise);
      }
      if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        rubikCube.rotateR(clockwise);
      }
      if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        rubikCube.rotateF(clockwise);
      }
      if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        rubikCube.rotateB(clockwise);
      }
      if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        rubikCube.rotateU(clockwise);
      }
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        rubikCube.rotateD(clockwise);
      }
    }
  );

  window.run(
    [&rubikCube, &camera](float deltaTime) {
      camera.update();
      rubikCube.draw(deltaTime);
    }
  );

  return 0;
}
