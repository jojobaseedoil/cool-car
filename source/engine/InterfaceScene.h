#pragma once

#include "shader.h"

class Actor;
class Camera;
class DrawComponent;

class InterfaceScene{
public:
    virtual ~InterfaceScene() = default;

    virtual bool StartScene() = 0;
    virtual void EndScene() = 0;
    virtual void MainLoop() = 0;
    /* getters */
    virtual const Shader &GetProgram() const = 0;       /* get shader program */
    virtual const glm::mat4 &GetProjection() const = 0; /* get projection matrix */
    virtual const glm::mat4 &GetView() const = 0;       /* get view matrix */
    virtual Camera *GetCamera() const = 0;

    /* setters */
    virtual void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar) = 0;
    virtual void SetPerspective(float fovy, float aspect, float zNear, float zFar) = 0;
    virtual void SetWireFrame(bool mode) = 0;
    
    virtual void AddActor(Actor *actor) = 0;
    virtual void RemoveActor(Actor *actor) = 0;

    virtual void AddDrawable(DrawComponent *drawable) = 0;
    virtual void RemoveDrawable(DrawComponent *drawable) = 0;

private:
    virtual void ProcessInput() = 0;
    virtual void RenderScene() = 0;
    virtual void UpdateScene() = 0;
};