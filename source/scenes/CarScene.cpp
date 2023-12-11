#include "CarScene.h"
#include "../engine/actors/camera.h"
#include "../engine/actors/car.h"

CarScene::CarScene(GLint WindowWidth, GLint WindowHeight):
    ConcreteScene(WindowWidth, WindowHeight)
{

}

void CarScene::CreateScene(){

    const glm::vec3 eye(0,0,10);
    const glm::vec3 center(0,0,0);
    const glm::vec3 up(0,1,0);
    mCamera = new Camera(this,eye,center,up);
    // glm::mat4 view = glm::rotate(mCamera->GetView(),glm::radians(90.0f),glm::vec3(0,0,1));
    // mCamera->SetView(view);
    // SetPerspective(0.75, 1, 1, 200);
    SetOrtho(-20,20,-20,20,-50,50);
    
    mCar = new Car(this);
}