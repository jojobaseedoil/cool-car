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
    mSpeed(NEUTRAL_GEAR_SPEED),
    mCurrentGear(0),
    mCanProcessInput(false)
{   
    new DrawComponent(this, "../models/cool-car.obj");
    new RigidBodyComponent(this, 1, 4);

    mGearBox[0] = NEUTRAL_GEAR_SPEED;
    mGearBox[1] = FIRST_GEAR_SPEED;
    mGearBox[2] = SECOND_GEAR_SPEED;
    mGearBox[3] = THIRD_GEAR_SPEED;
    mGearBox[4] = REVERSE_GEAR;

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

    // std::cout << GetPosition().x << " ";
    // std::cout << GetPosition().y << " ";
    // std::cout << GetPosition().z << "\n\n";

    /* simple input handle system */
    static float timer = 0;
    timer += DeltaTime;
    if(timer >= 1.0f){ /* wait 1 second */
        mCanProcessInput = true;
        timer = 0.0f;
    }
}

void Car::OnProcessInput(GLFWwindow *window){

    if( glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) ){ /* press shift for reverse gear */

        mSpeed = mGearBox[4];

    } else if( glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && mCanProcessInput){ /* change gears */
        mCurrentGear = (mCurrentGear+1)%4;
        mSpeed = mGearBox[mCurrentGear];
        mCanProcessInput = false;
    } else { /* move with the current gear */
        mSpeed = mGearBox[mCurrentGear];
    }

    /* move up */
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ){
        Move(glm::vec3(0,1,0)*mSpeed);
        SetRotation(0);
    } 

    /* move to right */
    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,0,0)*mSpeed);
        SetRotation(-90);
    }

    /* move to down */
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ){
        Move(glm::vec3(0,-1,0)*mSpeed);
        SetRotation(180);
    } 

    /* move to left */
    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,0,0)*mSpeed);
        SetRotation(90);
    }
    
    /* move up right */
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,1,0)*mSpeed/4.0f);
        SetRotation(-45);
    }

    /* move up left */
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,1,0)*mSpeed/4.0f);
        SetRotation(45);
    }  

    /* move down right */
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,-1,0)*mSpeed/4.0f);
        SetRotation(-135);
    }  

    /* move to down left */
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,-1,0)*mSpeed/4.0f);
        SetRotation(135);
    } 
}

void Car::Move(const glm::vec3 &force){
    
    this->GetComponent<RigidBodyComponent>()->ApplyForce(force);
    
    glm::vec3 CarPos = GetPosition();
    Camera *camera = mScene->GetCamera();
    camera->GetComponent<RigidBodyComponent>()->ApplyForce(force/4.0f);
}