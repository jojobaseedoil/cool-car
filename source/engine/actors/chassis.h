#pragma once

#include "actor.h"

class DrawComponent;

class Chassis : public Actor{
public:
    Chassis(InterfaceScene *scene);

private:
    DrawComponent *mDrawComponent;
};