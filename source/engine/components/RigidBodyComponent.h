#pragma once
#include "component.h"

class RigidBodyComponent : public Component {
public:
    // Lower update order to update first
    RigidBodyComponent(Actor* owner, float mass = 1.0f, float friction = 0.0f, int updateOrder = 10);

    void Update(float deltaTime) override;

    inline const glm::vec3& GetVelocity() const { return mVelocity; }
    inline void SetVelocity(const glm::vec3& velocity) { mVelocity = velocity; }

    inline const glm::vec3& GetAcceleration() const { return mAcceleration; }
    inline void SetAcceleration(const glm::vec3& acceleration) { mAcceleration = acceleration; }

    void ApplyForce(const glm::vec3 &force);

private:
    bool IsNearZero(const float val) const;

    // Physical properties
    float mFrictionCoefficient;
    float mMass;
    float m;

    glm::vec3 mVelocity;
    glm::vec3 mAcceleration;
};