#include "Object.hpp"

Object::Object(Shader& shader, float* vertices, int size) : shader(shader) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  this->resetTransformation();
}

// Object::Object(float[] vertices, int[] indices) {
//   glGenVertexArrays(1, &VAO);
//   glGenBuffers(1, &VBO);
//   // glGenBuffers(1, &EBO);

//   glBindVertexArray(VAO);

//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//   glEnableVertexAttribArray(0);
// }

Object::~Object() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  // glDeleteBuffers(1, &EBO);
}

void Object::draw() {
  this->transform();

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Object::transform() {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, this->translation);
  model = glm::rotate(model, this->rotationAngle, this->rotationAxis);
  model = glm::scale(model, this->scaling);

  this->shader.setMat4("model", model);
}

void Object::translate() {
  this->translate(glm::vec3(0.0f));
}
void Object::translate(glm::vec3 translation) {
  this->translation = translation;
}

void Object::rotate() {
  this->rotate(0.0f, glm::vec3(1.0f));
}
void Object::rotate(float angle, glm::vec3 axis) {
  this->rotationAngle = angle;
  this->rotationAxis = axis;
}

void Object::scale() {
  this->scale(glm::vec3(1.0f));
}
void Object::scale(glm::vec3 scaling) {
  this->scaling = scaling;
}

void Object::resetTransformation() {
  this->translate();
  this->rotate();
  this->scale();
}
