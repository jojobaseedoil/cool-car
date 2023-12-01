#include "RigidBodyComponent.h"
#include "../actors/actor.h"

const float MAX_SPEED_X = 300.0f;
const float MAX_SPEED_Y = 700.0f;

RigidBodyComponent::RigidBodyComponent(Actor* owner, float mass, float friction, int updateOrder)
        :Component(owner, updateOrder)
        ,mMass(mass)
        ,mFrictionCoefficient(friction)
        ,mVelocity(glm::vec3(0,0,0))
        ,mAcceleration(glm::vec3(0,0,0))
{

}

bool RigidBodyComponent::IsNearZero(const float val) const{
    float epsilon = glm::epsilon<float>();
    if(fabs(val) <= epsilon)
        return true;
    return false;
}

void RigidBodyComponent::ApplyForce(const glm::vec3 &force) {
    mAcceleration += force * (1.f/mMass);
}

void RigidBodyComponent::Update(float deltaTime)
{
    // Apply friction
    if(mVelocity.x != 0.0f) {
        ApplyForce(glm::vec3(1,0,0) * -mFrictionCoefficient * mVelocity.x);
    }
    if(mVelocity.y != 0.0f) {
        ApplyForce(glm::vec3(0,1,0) * -mFrictionCoefficient * mVelocity.y);
    }

    // Euler Integration
    mVelocity += mAcceleration * deltaTime;

    mVelocity.x = glm::clamp<float>(mVelocity.x, -MAX_SPEED_X, MAX_SPEED_X);
    mVelocity.y = glm::clamp<float>(mVelocity.y, -MAX_SPEED_Y, MAX_SPEED_Y);

    if(IsNearZero(mVelocity.x)) {
        mVelocity.x = 0.f;
    }
    if(IsNearZero(mVelocity.y)) {
        mVelocity.y = 0.f;
    }

    glm::vec3 position = mOwner->GetPosition();
    mOwner->SetPosition(position + mVelocity * deltaTime);
    // std::cout << position.x << " " << position.y << "\n";

    mAcceleration = glm::vec3(0,0,0);
}
