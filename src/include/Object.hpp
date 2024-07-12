#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>

class Object {
public:
  Object(float* vertices, int size);
  ~Object();

  void draw();

protected:
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
};

#endif
