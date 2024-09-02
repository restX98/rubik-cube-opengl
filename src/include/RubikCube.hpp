#ifndef RUBIK_CUBE_H
#define RUBIK_CUBE_H

#include <AnimatedModel.hpp>
#include <Shader.hpp>
#include <Cube.hpp>

#include <vector>

#define GAP 2.05f

#define GREEN glm::vec3(0.0f, 0.6078f, 0.2823f)
#define WHITE glm::vec3(1.0f, 1.0f, 1.0f)
#define RED glm::vec3(0.7176f, 0.0705f, 0.2039f)
#define YELLOW glm::vec3(1.0f, 0.8352f, 0.0f)
#define BLUE glm::vec3(0.0f, 0.2745f, 0.6784f)
#define ORANGE glm::vec3(1.0f, 0.3451f, 0.0f)

struct CubePosition {
  Cube* cube;
  int x;
  int y;
  int z;
};

class RubikCube : public AnimatedModel {
private:
  float speed = 2.5f;

  std::vector<std::vector<std::vector<CubePosition*>>> cubes;
  void generate(Shader* shader);
  void align();

  bool isTransitionL = false;
  bool isTransitionR = false;
  bool isTransitionF = false;
  bool isTransitionU = false;
  float rotationAngle;
  float rotationSpeed = 50.0f;

  void draw(glm::mat4 model) override;
  void updateAxis(CubePosition* c);
  void setTransition(Transition* transition);

public:
  RubikCube(Shader* shader);

  void draw(float deltaTime, glm::mat4 model = glm::mat4(1.0f));
  void translate(float x, float y, float z) override;
  void rotateX(float angle, float force = 1.0f) override;
  void rotateY(float angle, float force = 1.0f) override;
  void rotateZ(float angle, float force = 1.0f) override;
  void scale(float scaling) override;

  void rotateL(bool clockwise = true);
  void rotateR(bool clockwise = true);
  void rotateF(bool clockwise = true);
  void rotateB(bool clockwise = true);
  void rotateU(bool clockwise = true);
  void rotateD(bool clockwise = true);

protected:
  class FaceTransition : public Transition {
  private:
    RubikCube* rubikCube;
    float speed = 50.0f;
    bool clockwise;
    float angle;
    int CubePosition::* axis;
    int axisPos;
    void (Cube::* rotate)(float, float);
    glm::vec3 faceNormal;

  public:
    FaceTransition(RubikCube* rc, Face face, bool clockwise = true);

    void update(float deltaTime) override;
  };
};

#endif
