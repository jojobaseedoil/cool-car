#include "light.h"

Light::Light(InterfaceScene *scene):
    Actor(scene)
{

}

void Light::OnUpdate(float DeltaTime){
    Shader program = mScene->GetProgram();
    program.use();
    program.SetVec3f("light_position", mPosition);
}