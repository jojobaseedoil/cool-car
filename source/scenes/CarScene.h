#pragma once

#include "../engine/ConcreteScene.h"

class CarScene : public ConcreteScene{
public:
    CarScene(GLint WindowWidth, GLint WindowHeight);

    /* Scene specific */
    void CreateScene() override;
};