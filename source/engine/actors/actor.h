#pragma once

#include "../InterfaceScene.h"

#define MIN_WHEEL_ROTATION -0.4f
#define MAX_WHEEL_ROTATION 0.4f

class Component;
class Texture;

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
    void SetPosition(const glm::vec3 &position);

    const glm::vec3 &GetRotation() const;
    void SetRotation(const glm::vec3 &rotation);

    const glm::vec3 &GetScale() const;
    void SetScale(const glm::vec3 &scale);
    
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

    std::vector<Texture*> GetTextures() const{
        std::vector<Texture*> textures;
        textures.push_back(mDiffuse);
        textures.push_back(mSpecular);
        return textures;
    }
    void SetTextures(Texture *diffuse, Texture *specular){
        mDiffuse = diffuse;
        mSpecular = specular;
    }

protected:

    virtual void OnProcessInput(GLFWwindow *window);
    virtual void OnUpdate(float DeltaTime);

    InterfaceScene *mScene;
    
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;

    ActorState mState;

    std::vector<Component*> mComponents;
    glm::mat4 mModelMatrix;

    Texture *mDiffuse;
    Texture *mSpecular;

private:
    friend class Component;
    void AddComponent(Component* c);
};