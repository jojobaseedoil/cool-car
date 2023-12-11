#pragma once

#include "../InterfaceScene.h"

#define MIN_WHEEL_ROTATION -0.4f
#define MAX_WHEEL_ROTATION 0.4f

class Component;

enum class ActorState{
    Active,
    Paused,
    Destroy
};

class Actor {
public:
    explicit Actor(InterfaceScene *scene);
    virtual ~Actor();

    void Update(float DeltaTime);
    void ProcessInput(GLFWwindow *window);

    const glm::vec3 &GetPosition() const;
    void SetPosition(const glm::vec3 &pos);

    float GetRotation() const;
    void SetRotation(float rot);

    glm::vec3 GetForward() const;
    
    const glm::mat4 &GetModel() const;
    void SetModel(const glm::mat4 &model);

    InterfaceScene *GetScene() const;

    template <typename T>
    T* GetComponent() const {
        for (auto c : mComponents) {
            T* t = dynamic_cast<T*>(c);
            if (t != nullptr)
                return t;
        }
        return nullptr;
    }

protected:

    virtual void OnProcessInput(GLFWwindow *window);
    virtual void OnUpdate(float DeltaTime);

    InterfaceScene *mScene;
    
    glm::vec3 mPosition;
    ActorState mState;
    float mRotation;

    std::vector<Component*> mComponents;
    glm::mat4 mModelMatrix;

private:
    friend class Component;
    void AddComponent(Component* c);
};