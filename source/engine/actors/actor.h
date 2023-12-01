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

    inline const glm::vec3 &GetPosition() const{
        return mPosition;
    }
    inline void SetPosition(const glm::vec3 &pos){
        mPosition = pos;
        SetModel(glm::translate(glm::mat4(1), mPosition));
    }
    inline float GetRotation() const{
        return mRotation;
    }
    inline void SetRotation(float rot){
        rot = glm::clamp<float>(rot,MIN_WHEEL_ROTATION,MAX_WHEEL_ROTATION);
        mRotation = rot;
        mModelMatrix = glm::rotate(mModelMatrix, mRotation, glm::vec3(0,0,1));
    }
    inline glm::vec3 GetForward() const { return glm::vec3(glm::cos(mRotation), -glm::sin(mRotation), 0); }
    inline const glm::mat4 &GetModel() const{ return mModelMatrix; }
    inline void SetModel(const glm::mat4 &model){ mModelMatrix = model; }

    inline InterfaceScene *GetScene() const { return mScene; }

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
    float mRotation;
    std::vector<Component*> mComponents;
    glm::mat4 mModelMatrix;
    ActorState mState;

private:
    friend class Component;
    void AddComponent(Component* c);
};