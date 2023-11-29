#include "CarScene.h"

CarScene::CarScene(GLint WindowWidth, GLint WindowHeight):
    ConcreteScene(WindowWidth, WindowHeight)
{

}

void CarScene::CreateScene(){

    const glm::vec3 eye(0, 0, 40);
    const glm::vec3 center(0, 0, 0);
    const glm::vec3 up(0, 1, 0);

    mCamera = new Camera(this, eye, center, up);

    SetPerspective(0.75, 1, 1, 200);

    auto chassis = new DrawableObject(this, "../models/chassis.obj");
    // auto wheels = new DrawableObject(this, "../models/wheels.obj");
    mDrawables.emplace_back(chassis);
}