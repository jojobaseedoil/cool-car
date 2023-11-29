#pragma once

#include "InterfaceScene.h"

class InterfaceObject{

public:
	virtual ~InterfaceObject() = default;
	virtual void Update(float DeltaTime) = 0;
	virtual void ProcessInput(GLFWwindow *window) = 0;
};