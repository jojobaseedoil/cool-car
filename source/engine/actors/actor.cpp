#include "actor.h"
#include "../components/component.h"
#include <algorithm>

Actor::Actor(InterfaceScene *scene):
    mPosition(glm::vec3(0,0,0)),
    mRotation(0.0f),
    mScene(scene),
    mState(ActorState::Active),
    mModelMatrix(glm::mat4(1))
{
    mScene->AddActor(this);
}

Actor::~Actor(){
    mScene->RemoveActor(this);

    for(auto component : mComponents){
        delete component;
    }
    mComponents.clear();
}

void Actor::Update(float DeltaTime){
    
    if (mState == ActorState::Active) {
        for (auto comp : mComponents) {
            if(comp->IsEnabled())
                comp->Update(DeltaTime);
        }

        OnUpdate(DeltaTime);
    }
}

void Actor::OnUpdate(float DeltaTime){

}

void Actor::ProcessInput(GLFWwindow *window){
    if (mState == ActorState::Active)
    {
        for (auto comp : mComponents)
        {
            comp->ProcessInput(window);
        }

        OnProcessInput(window);
    }
}

void Actor::OnProcessInput(GLFWwindow *window){

}

void Actor::AddComponent(Component* c){
    mComponents.emplace_back(c);
    std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
        return a->GetUpdateOrder() < b->GetUpdateOrder();
    });
}