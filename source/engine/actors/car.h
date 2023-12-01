#pragma once

#include "actor.h"

class Wheel;
class Chassis;

class Car : public Actor{
public:
    Car(InterfaceScene *scene);

    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(GLFWwindow *window) override;

private:
    Chassis *mChassis;
    std::vector<Wheel*> mWheels;
    glm::vec3 mPivo;
    float mSteeringAngle;
};