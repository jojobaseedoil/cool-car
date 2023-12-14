#include "car.h"
#include "camera.h"
#include "wheel.h"
#include "../components/RigidBodyComponent.h"
#include "../components/drawables/DrawComponent.h"
#include "../components/texture.h"
#include "../components/material.h"

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
    // new DrawComponent(this, "../models/cool-car.obj");
    // new RigidBodyComponent(this, 1, 4);
    // new Texture(this, "../models/container.jpg", GL_TEXTURE_2D);
    
    // const glm::vec3 ambient(0.5f);
    // const glm::vec3 diffuse(1.f);
    // const glm::vec3 specular(1.f);
    // const GLint diffuseTexture  = 0;
    // const GLint specularTexture = 0;
    // new Material(this, ambient, diffuse, specular, diffuseTexture, specularTexture);

    mGearBox[0] = NEUTRAL_GEAR_SPEED;
    mGearBox[1] = FIRST_GEAR_SPEED;
    mGearBox[2] = SECOND_GEAR_SPEED;
    mGearBox[3] = THIRD_GEAR_SPEED;
    mGearBox[4] = REVERSE_GEAR;

    // for(int i=0; i<100; i++){
    //     Wheel *w = new Wheel(scene, false);
    //     w->SetPosition(glm::vec3(0,10*i,-10));
    // }
}

void Car::OnUpdate(float DeltaTime){
    
    mModelMatrix = glm::mat4(1.f);
    mModelMatrix = glm::translate(mModelMatrix, mPosition);
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.x), glm::vec3(1.f,0.f,0.f));
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.y), glm::vec3(0.f,1.f,0.f));
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.z), glm::vec3(0.f,0.f,1.f));
    mModelMatrix = glm::scale(mModelMatrix, mScale);
    

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
        SetRotation(glm::vec3(-90, 0, 180));
    } 

    /* move to down */
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ){
        Move(glm::vec3(0,-1,0)*mSpeed);
        SetRotation(glm::vec3(90, 0, 0));
    } 
    /* move to right */
    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,0,0)*mSpeed);
        SetRotation(glm::vec3(0,90,90));
    }


    /* move to left */
    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,0,0)*mSpeed);
        SetRotation(glm::vec3(0, -90, -90));
    }
    
    /* move up right */
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,1,0)*mSpeed/4.0f);
        // rotation.z = -45.0f;
        SetRotation(glm::vec3(90, 135, 0));
    }

    /* move up left */
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,1,0)*mSpeed/4.0f);
        SetRotation(glm::vec3(90, -135, 0));
    }  

    /* move down right */
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        Move(glm::vec3(1,-1,0)*mSpeed/4.0f);
        SetRotation(glm::vec3(90, 45, 0));
    }  

    /* move to down left */
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        Move(glm::vec3(-1,-1,0)*mSpeed/4.0f);
        SetRotation(glm::vec3(90, -45, 0));
    } 
}

void Car::Move(const glm::vec3 &force){
    
    this->GetComponent<RigidBodyComponent>()->ApplyForce(force);
    
    glm::vec3 CarPos = GetPosition();
    Camera *camera = mScene->GetCamera();
    camera->GetComponent<RigidBodyComponent>()->ApplyForce(force/4.0f);
}