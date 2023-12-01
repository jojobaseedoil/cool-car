#pragma once

#include "actor.h"

class Camera : public Actor{

public:
	Camera(InterfaceScene *owner, const glm::vec3&eye, const glm::vec3&center, const glm::vec3&up);
	~Camera();

	void OnUpdate(float DeltaTime) override;
	void OnProcessInput(GLFWwindow *window) override;
	void LookAt(const glm::vec3&eye, const glm::vec3&center, const glm::vec3&up);
private:
	friend class ConcreteScene;
	glm::mat4 mViewMatrix;
	glm::vec3 mEye, mCenter, mUp;
};