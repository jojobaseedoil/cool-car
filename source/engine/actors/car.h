#pragma once

#include "actor.h"

#define NEUTRAL_GEAR_SPEED 0.0f
#define FIRST_GEAR_SPEED 100.0f
#define SECOND_GEAR_SPEED 150.0f
#define THIRD_GEAR_SPEED 175.0f
#define REVERSE_GEAR -50.0f

class Wheel;
class Chassis;
class RigidBodyComponent;

class Car : public Actor{
public:
    Car(InterfaceScene *scene);

    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(GLFWwindow *window) override;

    void Move(const glm::vec3 &force);
private:
    float mCarWidth, mCarHeight;
    float mGearBox[5]; // marcha do carro
    float mSpeed;
    int mCurrentGear;
    bool mCanProcessInput;
};