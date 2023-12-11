#pragma once

#include "../components/drawables/DrawComponent.h"
#include "../components/RigidBodyComponent.h"

class Car;

class Wheel : public Actor{
public:
    Wheel(InterfaceScene *scene, bool enabled);

    void OnUpdate(float DeltaTime) override;    
    void OnProcessInput(GLFWwindow *window) override;
    bool IsFrontWheel() const;

private:
    bool mIsFrontWheel;
    DrawComponent *mDrawComponent;
    RigidBodyComponent *mRigidBodyComponent;
};