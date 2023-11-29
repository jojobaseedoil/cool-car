#include "camera.h"

Camera::Camera(InterfaceScene *owner, const glm::vec3&eye, const glm::vec3&center, const glm::vec3&up):
    mUp(up),
	mEye(eye),
	mOwner(owner),
    mCenter(center),
    mViewMatrix(glm::mat4(1.0))
{
	LookAt(eye,center,up);
}

Camera::~Camera(){

}

void Camera::LookAt(const glm::vec3&eye, const glm::vec3&center, const glm::vec3&up){
    const glm::vec3 f(glm::normalize(eye - center));
	const glm::vec3 s(glm::normalize(glm::cross(up, f)));
	const glm::vec3 u(glm::cross(f, s));
	
	mViewMatrix = glm::mat4(1.0);
	mViewMatrix[0][0] = s.x;
	mViewMatrix[1][0] = s.y;
	mViewMatrix[2][0] = s.z;
	
	mViewMatrix[0][1] = u.x;
	mViewMatrix[1][1] = u.y;
	mViewMatrix[2][1] = u.z;

	mViewMatrix[0][2] = f.x;
	mViewMatrix[1][2] = f.y;
	mViewMatrix[2][2] = f.z;

	mViewMatrix[3][0] = -glm::dot(s, eye);
	mViewMatrix[3][1] = -glm::dot(u, eye);
	mViewMatrix[3][2] = -glm::dot(f, eye);
}
    
void Camera::ProcessInput(GLFWwindow *window){
	/* Process Camera Input here... */
}

void Camera::Update(float DeltaTime){
    /* Update Camera here... */
}