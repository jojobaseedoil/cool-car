#include "wheel.h"

Wheel::Wheel(InterfaceScene *scene, bool enabled):
    Actor(scene),
    mIsFrontWheel(enabled)
{
    mDrawComponent = new DrawComponent(this, "../models/wheel.obj");
    mRigidBodyComponent = new RigidBodyComponent(this, 1, 4);
}

void Wheel::OnUpdate(float DeltaTime){
    glm::mat4 tMatrix = glm::translate(glm::mat4(1),mPosition);
    glm::mat4 model = glm::rotate(tMatrix,glm::radians(mRotation),glm::vec3(0,0,1));
    SetModel(model);
}

void Wheel::OnProcessInput(GLFWwindow *window){

}

bool Wheel::IsFrontWheel() const{
    return mIsFrontWheel;
}