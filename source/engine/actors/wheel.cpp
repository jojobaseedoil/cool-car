#include "wheel.h"

Wheel::Wheel(InterfaceScene *scene, bool enabled):
    Actor(scene),
    mIsFrontWheel(enabled)
{
    mDrawComponent = new DrawComponent(this, "../models/wheel.obj");
    mRigidBodyComponent = new RigidBodyComponent(this, 1, 4);
}

void Wheel::OnUpdate(float DeltaTime){
    mModelMatrix = glm::mat4(1.f);
    mModelMatrix = glm::translate(mModelMatrix, mPosition);
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.x), glm::vec3(1.f,0.f,0.f));
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.y), glm::vec3(0.f,1.f,0.f));
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.z), glm::vec3(0.f,0.f,1.f));
}

void Wheel::OnProcessInput(GLFWwindow *window){

}

bool Wheel::IsFrontWheel() const{
    return mIsFrontWheel;
}