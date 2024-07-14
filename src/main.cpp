#include <glad/glad.h>

#include <iostream>
#include "Window.hpp"
#include "Shader.hpp"
#include "Object.hpp"
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

  float vertices[] = {
   // Positions          Texture coords
   -0.5f, -0.5f, -0.5f, // 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, // 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
    0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f, // 0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f, // 0.0f, 0.0f,

   -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, // 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f, // 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, // 1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f, // 0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,

   -0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
   -0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
   -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
   -0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,

    0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,

   -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, // 1.0f, 1.0f,
    0.5f, -0.5f,  0.5f, // 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f, // 1.0f, 0.0f,
   -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
   -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,

   -0.5f,  0.5f, -0.5f, // 0.0f, 1.0f,
    0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f, // 0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f, // 0.0f, 1.0f
  };

  Object cube(shader, vertices, sizeof(vertices));


  window.run(
    [&shader, &cube]() {
      shader.use();

      cube.translate(glm::vec3(0.5f, -0.5f, 0.0f));
      float value = static_cast<float>((sin(glfwGetTime()) + 1) / 2);
      cube.scale(glm::vec3(value, value, value));
      cube.rotate((float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
      cube.draw();
    }
  );

  return 0;
}

/**
 * classe che gestisce openGL :
-Inizializza la finestra
- gestione callback
- gestione input keyboard / mouse
- distrugge la finestra in chiusura
- Renderizza gli oggetti

classe che definisce le figure(es quadrato 2D, cubo 3D, triangolo 2D ecc) :
  -Definisce i vertici / indici
  - Crea o buffer
  - Assegna le textures

  classe che gestisce la camera
  - Definisce la lookAt matrix
  - Gestisce i movimenti
 */
