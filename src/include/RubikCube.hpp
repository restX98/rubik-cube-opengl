#ifndef RUBIK_CUBE_H
#define RUBIK_CUBE_H

#include <unordered_map>
#include <vector>

#include "AnimatedModel.hpp"
#include "Cube.hpp"

#define GAP 2.05f

#define GREEN glm::vec3(0.0f, 0.6078f, 0.2823f)
#define WHITE glm::vec3(1.0f, 1.0f, 1.0f)
#define RED glm::vec3(0.7176f, 0.0705f, 0.2039f)
#define YELLOW glm::vec3(1.0f, 0.8352f, 0.0f)
#define BLUE glm::vec3(0.0f, 0.2745f, 0.6784f)
#define ORANGE glm::vec3(1.0f, 0.3451f, 0.0f)

class RubikCube : public AnimatedModel {
protected:
  class Cubby : public Cube {
  private:
    friend class RubikCube;

  protected:
    Cubby(Shader* shader, int x, int y, int z);

    int x;
    int y;
    int z;

    void setPivot(float x, float y, float z);
    void updateAxis();
  };

private:
  std::vector<std::vector<std::vector<RubikCube::Cubby*>>> cubes;
  std::unordered_map<Face, Face> faceMapping = {
    {Face::FRONT_FACE, Face::FRONT_FACE},
    {Face::BACK_FACE, Face::BACK_FACE},
    {Face::LEFT_FACE, Face::LEFT_FACE},
    {Face::RIGHT_FACE, Face::RIGHT_FACE},
    {Face::TOP_FACE, Face::TOP_FACE},
    {Face::BOTTOM_FACE, Face::BOTTOM_FACE}
  };

  void draw(glm::mat4 model = glm::mat4(1.0f)) override;
  void generate(Shader* shader);

public:
  RubikCube(Shader* shader);

  void draw(float deltaTime, glm::mat4 model = glm::mat4(1.0f));
  void translate(float x, float y, float z) override;

  void turnRight();
  void turnLeft();
  void turnUpsideDown();

  void rotateL(bool clockwise = true);
  void rotateR(bool clockwise = true);
  void rotateF(bool clockwise = true);
  void rotateB(bool clockwise = true);
  void rotateU(bool clockwise = true);
  void rotateD(bool clockwise = true);

  void switchPOV(bool reverse);

protected:
  enum class Axis {
    X,
    Y,
    Z
  };

  class FaceTransition : public Transition {
  private:
    RubikCube* rubikCube;
    float speed = 150.0f;
    int sign;
    float angle;
    int RubikCube::Cubby::* axis;
    int axisPos;
    void (Cube::* rotate)(float, float);
    glm::vec3 faceNormal;

  public:
    FaceTransition(RubikCube* rc, Face face, bool clockwise = true);

    void update(float deltaTime) override;
  };

  class POVTransition : public Transition {
  private:
    RubikCube* rubikCube;
    float speed = 250.0f;

    void (RubikCube::* rotate)(float, float);
    float angle;
    float endingAngle;
    int sign;

  public:
    POVTransition(RubikCube* rc, float startingAngle, float endingAngle, Axis axis = Axis::X);

    void update(float deltaTime) override;
  };
};

#endif
