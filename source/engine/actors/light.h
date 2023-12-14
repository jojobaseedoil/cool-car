#pragma once

#include "actor.h"

class Light : public Actor{
public:
    Light(InterfaceScene *scene);
    void OnUpdate(float DeltaTime) override;
};