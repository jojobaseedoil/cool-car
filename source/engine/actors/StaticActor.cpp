#include "StaticActor.h"

StaticActor::StaticActor(InterfaceScene *scene):
    Actor(scene)
{

}

void StaticActor::OnUpdate(float DeltaTime){
    mModelMatrix = glm::mat4(1.f);
    mModelMatrix = glm::translate(mModelMatrix, mPosition);
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.x), glm::vec3(1.f,0.f,0.f));
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.y), glm::vec3(0.f,1.f,0.f));
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.z), glm::vec3(0.f,0.f,1.f));
    mModelMatrix = glm::scale(mModelMatrix, mScale);
}