#pragma once

#include "InterfaceScene.h"

#define INITIALIZE_FAILURE 0
#define INITIALIZE_SUCCESS 1

class Camera;
class Actor;

class ConcreteScene : public InterfaceScene{
public:
    
    /* Constructors and destructor */
    ConcreteScene(GLint WindowWidth, GLint WindowHeight);
    virtual ~ConcreteScene();

    /* Scene main methods */
    bool StartScene() override;
    void EndScene() override;
    void MainLoop() override;

    /* Getters */
    inline const Shader &GetProgram() const override{
        return mProgram;
    }
    inline const glm::mat4 &GetProjection() const override{
        return mProjectionMatrix;
    }
    const glm::mat4 &GetView() const override;
    Camera *GetCamera() const override;
    
    /* Setters */
    void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar) override;
    void SetPerspective(float fovy, float aspect, float zNear, float zFar) override;
    void SetWireFrame(bool mode) override;

    /* Scene specific */
    virtual void CreateScene();

    void AddActor(Actor *actor) override;
    void RemoveActor(Actor *actor) override;

    void AddDrawable(DrawComponent *drawable) override;
    void RemoveDrawable(DrawComponent *drawable) override;

private:
	/* Private Methods */
	virtual void ProcessInput() override;
	virtual void RenderScene() override;
	virtual void UpdateScene() override;

protected:

    /* Attributes */
	GLFWwindow *mWindow;
	GLint mWindowWidth, mWindowHeight;

    Shader mProgram;
    Camera *mCamera;
    glm::mat4 mProjectionMatrix;
    std::vector<Actor*> mActors;
    std::vector<DrawComponent*> mDrawables;

    float mLastFrame;
};