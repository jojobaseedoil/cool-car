#pragma once

#include "../engine/ConcreteScene.h"

class Car;

class CarScene : public ConcreteScene{
public:
    CarScene(GLint WindowWidth, GLint WindowHeight);

    /* Scene specific */
    void CreateScene() override;
private:
    Car *mCar;
};