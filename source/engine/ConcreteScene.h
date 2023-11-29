#pragma once

#include "camera.h"
#include "DrawableObject.h"

#define INITIALIZE_FAILURE 0
#define INITIALIZE_SUCCESS 1

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
    inline const glm::mat4 &GetView() const override{
        return mCamera->mViewMatrix;
    }
    /* Setters */
    void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar) override;
    void SetPerspective(float fovy, float aspect, float zNear, float zFar) override;
    void SetWireFrame(bool mode) override;

    /* Scene specific */
    virtual void CreateScene();

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
    std::vector<DrawableObject*> mDrawables;
    
    float mLastFrame;
};