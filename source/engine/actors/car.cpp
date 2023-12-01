#include "car.h"
#include "chassis.h"
#include "wheel.h"

#define CAR_FORWARD_SPEED 10.0f
#define ROTATION_OFFSET 0.01f

Car::Car(InterfaceScene *scene):
    Actor(scene),
    mSteeringAngle(0.0)
{
    // mChassis = new Chassis(scene);
    // mChassis->SetModel(glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(1,0,0)));
    // mChassis->SetModel(glm::translate(mChassis->GetModel(), glm::vec3(1,2,-2)));
    float xOffset = 2.0f;
    float yOffset = 5.0f;
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            Wheel *w = new Wheel(scene, i*true);
            mWheels.emplace_back(w);
            w->SetPosition( glm::vec3( j*xOffset, i*yOffset, 0 ) );
        }
    }
    // mPivo = glm::vec3(0,0,0);
}

void Car::OnUpdate(float DeltaTime){
    // for(int i=0; i<4; i++){
    //     std::cout << mWheels[i]->GetRotation() << " ";
    // } std::cout << "\n";
    // mPivo = 

    // auto p1 = mWheels[0]->GetPosition();
    // auto p2 = mWheels[2]->GetPosition();
    // auto p3 = mWheels[1]->GetPosition();
    // auto u = p3 - p1;
    // auto v = p2 - p1;

    // std::cout << mWheels[0]->GetPosition().y << " " << v.length()/2 << "\n";

    // mPivo = glm::vec3(p3.x - u.length()/2, p2.y - v.length()/2, 0);

    // mChassis->SetPosition(mPivo);
}

void Car::OnProcessInput(GLFWwindow *window){

    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ){

        for(auto wheel : mWheels){
            auto rb = wheel->GetComponent<RigidBodyComponent>();
            rb->ApplyForce(glm::vec3(0,1,0) * CAR_FORWARD_SPEED);
        }

    }

    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        mSteeringAngle += ROTATION_OFFSET;
    } 


    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ){
        for(auto wheel : mWheels){
            auto rb = wheel->GetComponent<RigidBodyComponent>();
            rb->ApplyForce(glm::vec3(0,1,0) * -CAR_FORWARD_SPEED);
        }
    } 


    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        mSteeringAngle -= ROTATION_OFFSET;
    } 
}