#pragma once

#include "actor.h"

class StaticActor : public Actor{
public:
    StaticActor(InterfaceScene *scene);
    void OnUpdate(float DeltaTime) override;

};