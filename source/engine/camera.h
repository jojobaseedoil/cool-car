#pragma once

#include "InterfaceObject.h"

class Camera : public InterfaceObject{

public:
	Camera(InterfaceScene *owner, const glm::vec3&eye, const glm::vec3&center, const glm::vec3&up);
	~Camera();

	virtual void Update(float DeltaTime) override;
	virtual void ProcessInput(GLFWwindow *window) override;
	void LookAt(const glm::vec3&eye, const glm::vec3&center, const glm::vec3&up);
private:
	friend class ConcreteScene;
	InterfaceScene *mOwner;
	glm::mat4 mViewMatrix;
	glm::vec3 mEye, mCenter, mUp;
};