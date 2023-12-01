#include "component.h"
#include "../actors/actor.h"

Component::Component(Actor* owner, int updateOrder):
    mOwner(owner),
    mUpdateOrder(updateOrder),
    mIsEnabled(true)
{
    mOwner->AddComponent(this);
}

Component::Component():
    mOwner(nullptr),
    mUpdateOrder(100),
    mIsEnabled(false)
{
    
}

Component::~Component(){

}

void Component::Update(float deltaTime){

}

void Component::ProcessInput(GLFWwindow *window){

}