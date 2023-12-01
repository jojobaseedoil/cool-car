#include "wheel.h"


Wheel::Wheel(InterfaceScene *scene, bool enabled):
    Actor(scene),
    mIsWheelEnabled(enabled)
{
    mDrawComponent = new DrawComponent(this, "../models/wheel.obj");
    mRigidBodyComponent = new RigidBodyComponent(this, 1, 4);
}

void Wheel::OnUpdate(float DeltaTime){

}

void Wheel::OnProcessInput(GLFWwindow *window){

    
}