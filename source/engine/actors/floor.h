#pragma once

#include "actor.h"

class Floor : public Actor{
public:
    Floor(InterfaceScene *scene);
    void OnUpdate(float DeltaTime) override;

};