#include "camera.h"
#include "../components/RigidBodyComponent.h"

Camera::Camera(InterfaceScene *owner, const glm::vec3&eye, const glm::vec3&center, const glm::vec3&up):
	Actor(owner),
    mUp(up),
	mEye(eye),
    mCenter(center),
    mViewMatrix(glm::mat4(1.0))
{
	LookAt(eye,center,up);
	new RigidBodyComponent(this, 1, 1);
}

Camera::~Camera(){

}

void Camera::LookAt(const glm::vec3&eye, const glm::vec3&center, const glm::vec3&up){
	mViewMatrix = glm::lookAt(eye,center,up);
}
    
void Camera::OnProcessInput(GLFWwindow *window){
	/* Process Camera Input here... */
}

void Camera::OnUpdate(float DeltaTime){
    /* Update Camera here... */
    const glm::vec3 eye(mPosition.x,mPosition.y-15,10);
    const glm::vec3 center(mPosition.x, mPosition.y,0);
    const glm::vec3 up(0,1,0);
    this->LookAt(eye, center, up);
}

const glm::mat4 &Camera::GetView() const{
	return mViewMatrix;
}

void Camera::SetView(const glm::mat4 &view){
	mViewMatrix = view;
}