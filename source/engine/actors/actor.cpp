#include "actor.h"
#include "../components/component.h"
#include <algorithm>
#include "../components/texture.h"

Actor::Actor(InterfaceScene *scene):
    mPosition(glm::vec3(0.f,0.f,0.f)),
    mRotation(glm::vec3(0.f,0.f,0.f)),
    mScale(glm::vec3(1.f,1.f,1.f)),
    mScene(scene),
    mState(ActorState::Active),
    mModelMatrix(glm::mat4(1)),
    mDiffuse(nullptr),
    mSpecular(nullptr)
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

const glm::vec3 &Actor::GetPosition() const{
    return mPosition;
}

void Actor::SetPosition(const glm::vec3 &position){
    mPosition = position;
}

const glm::vec3 &Actor::GetRotation() const{
    return mRotation;
}

void Actor::SetRotation(const glm::vec3 &rotation){
    mRotation = rotation;
}

const glm::vec3 &Actor::GetScale() const{
    return mScale;
}

void Actor::SetScale(const glm::vec3 &scale){
    mScale = scale;
}

const glm::mat4 &Actor::GetModel() const{ 
    return mModelMatrix; 
}

void Actor::SetModel(const glm::mat4 &model){ 
    mModelMatrix = model; 
}

InterfaceScene *Actor::GetScene() const { 
    return mScene; 
}