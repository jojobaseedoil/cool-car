#include "car.h"
#include "camera.h"
#include "wheel.h"
#include "../components/RigidBodyComponent.h"
#include "../components/drawables/DrawComponent.h"

#define CAR_FORWARD_SPEED 75.0f
#define CAR_WIDTH 4.0f
#define CAR_HEIGHT 4.0f

#define FRONT_WHEEL_ROTATION_RATE 1.25f
#define FRONT_WHEEL_MAX_ANGLE 45.0f

Car::Car(InterfaceScene *scene):
    Actor(scene),
    mCarWidth(CAR_WIDTH),
    mCarHeight(CAR_HEIGHT),
    mCameraDelay(0.0f)
{   
    new DrawComponent(this, "../models/cool-car.obj");
    new RigidBodyComponent(this, 1, 4);


    for(int i=0; i<100; i++){
        Wheel *w = new Wheel(scene, false);
        w->SetPosition(glm::vec3(0,10*i,0));
    }
}

void Car::OnUpdate(float DeltaTime){
    
    glm::mat4 TranslateMatrix = glm::translate(glm::mat4(1), mPosition);
    glm::mat4 RotationMatrix  = glm::rotate(TranslateMatrix,glm::radians(mRotation),glm::vec3(0,0,1));
    RotationMatrix = glm::rotate(RotationMatrix, glm::radians(-90.0f), glm::vec3(1,0,0));
    RotationMatrix = glm::rotate(RotationMatrix, glm::radians(-180.0f), glm::vec3(0,0,1));
    SetModel(RotationMatrix);

    std::cout << GetPosition().x << " ";
    std::cout << GetPosition().y << " ";
    std::cout << GetPosition().z << "\n\n";
}

void Car::OnProcessInput(GLFWwindow *window){

    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ){
        Move(glm::vec3(0,1,0), CAR_FORWARD_SPEED);
        SetRotation(0);
    } 

    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,0,0), CAR_FORWARD_SPEED);
        SetRotation(-90);
    }

    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ){
        Move(glm::vec3(0,-1,0), CAR_FORWARD_SPEED);
        SetRotation(180);
    } 

    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,0,0), CAR_FORWARD_SPEED);
        SetRotation(90);
    }

    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,1,0), CAR_FORWARD_SPEED/4);
        SetRotation(-45);
    }

    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,1,0), CAR_FORWARD_SPEED/4);
        SetRotation(45);
    }  

    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,-1,0), CAR_FORWARD_SPEED/4);
        SetRotation(-135);
    }  

    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,-1,0), CAR_FORWARD_SPEED/4);
        SetRotation(135);
    }  
}

void Car::Move(const glm::vec3 &dir, const float speed){
    
    this->GetComponent<RigidBodyComponent>()->ApplyForce(dir*speed);
    
    glm::vec3 CarPos = GetPosition();
    Camera *camera = mScene->GetCamera();
    camera->GetComponent<RigidBodyComponent>()->ApplyForce(dir*(speed/4));
}