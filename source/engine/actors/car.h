#pragma once

#include "actor.h"

class Wheel;
class Chassis;
class RigidBodyComponent;

class Car : public Actor{
public:
    Car(InterfaceScene *scene);

    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(GLFWwindow *window) override;

    void Move(const glm::vec3 &dir, const float speed);
private:
    float mCarWidth, mCarHeight;
    float mCameraDelay;
};