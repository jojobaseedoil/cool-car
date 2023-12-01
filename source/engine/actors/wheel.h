#pragma once

#include "../components/drawables/DrawComponent.h"
#include "../components/RigidBodyComponent.h"

class Car;

class Wheel : public Actor{
    friend class Car;
public:
    Wheel(InterfaceScene *scene, bool enabled);

    void OnUpdate(float DeltaTime) override;    
    void OnProcessInput(GLFWwindow *window) override;

private:
    bool mIsWheelEnabled;
    DrawComponent *mDrawComponent;
    RigidBodyComponent *mRigidBodyComponent;
};