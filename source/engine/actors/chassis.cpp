#include "chassis.h"
#include "../components/drawables/DrawComponent.h"

Chassis::Chassis(InterfaceScene *scene):
    Actor(scene)
{
    mDrawComponent = new DrawComponent(this, "../models/chassis.obj");
}