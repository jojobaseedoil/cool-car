#pragma once

#include "../actors/actor.h"

class Component{
public:
    // Constructor
    // (the lower the update order, the earlier the component updates)
    explicit Component(Actor* owner, int updateOrder = 100);
    Component();
    // Destructor
    virtual ~Component();
    // Update this component by delta time
    virtual void Update(float deltaTime);
    // Process input for this component (if needed)
    virtual void ProcessInput(GLFWwindow *window);

    int GetUpdateOrder() const { return mUpdateOrder; }
    Actor* GetOwner() const { return mOwner; }
    // InterfaceScene* GetScene() const;

    void SetEnabled(const bool enabled) { mIsEnabled = enabled; };
    bool IsEnabled() const { return mIsEnabled; };

protected:
    // Owning actor
    Actor* mOwner;
    // Update order
    int mUpdateOrder;
    bool mIsEnabled;
};