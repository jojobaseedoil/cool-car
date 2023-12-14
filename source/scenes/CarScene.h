#pragma once

#include "../engine/ConcreteScene.h"

class Light;
class Car;

class CarScene : public ConcreteScene{
public:
    CarScene(GLint WindowWidth, GLint WindowHeight);

    /* Scene specific */
    void CreateScene() override;
private:
    Light *mLight;
    Car *mCar;
};