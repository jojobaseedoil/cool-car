#include "ConcreteScene.h"
#include "actors/camera.h"
#include "components/drawables/DrawComponent.h"
#include <algorithm>

/* Constructors and destructor */
ConcreteScene::ConcreteScene(GLint WindowWidth, GLint WindowHeight):
    mLastFrame(0.0f),
    mWindow(nullptr),
    mCamera(nullptr),
    mWindowWidth(WindowWidth),
    mWindowHeight(WindowHeight),
    mProjectionMatrix(glm::mat4(1.0f))
{

}


ConcreteScene::~ConcreteScene(){

}

/* Scene main methods */
bool ConcreteScene::StartScene(){
    
    /* Start GLFW for window management */
    if(!glfwInit()){
		std::cerr << "Could not initializate GLFW.\n";
		return INITIALIZE_FAILURE;
	}

    /* Set up some initial configs. */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create the project window and context */
    mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "LearnOpenGL", NULL, NULL);
    if (!mWindow){
        std::cerr << "Failed to create GLFW window" << std::endl;
        return INITIALIZE_FAILURE;
    }

    /* Associate this context to the current thread */
    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return INITIALIZE_FAILURE;
    }

    /* Create Shader program */
    mProgram = Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    /* Create your scene */
    CreateScene();

    return INITIALIZE_SUCCESS;
}

void ConcreteScene::EndScene(){
    // for(auto drawable : mDrawables)
    //     delete drawable;
    delete mCamera;  
    glfwDestroyWindow(mWindow);
    glDeleteProgram(mProgram.id);
    glfwTerminate();
}

void ConcreteScene::MainLoop(){
    while(!glfwWindowShouldClose(mWindow)){
        ProcessInput();
        RenderScene();
        UpdateScene();
    }
}

/* Setters */
void ConcreteScene::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar){
    mProjectionMatrix = glm::ortho(left,right,bottom,top,zNear,zFar);
}

void ConcreteScene::SetPerspective(float fovy, float aspect, float zNear, float zFar){
    mProjectionMatrix = glm::perspective(fovy,aspect,zNear,zFar);
}

void ConcreteScene::SetWireFrame(bool mode){
    // for(auto drawable : mDrawables)
        // drawable->SetWireFrame(mode);
}

const glm::mat4 &ConcreteScene::GetView() const{
    return mCamera->GetView();
}

Camera *ConcreteScene::GetCamera() const{
    return mCamera;
}

/* Scene specific */
void ConcreteScene::CreateScene(){
    /* create your scene here... */
}

void ConcreteScene::AddActor(Actor *actor){
    mActors.emplace_back(actor);
}

void ConcreteScene::RemoveActor(Actor *actor){
    auto it = std::find(mActors.begin(), mActors.end(), actor);
    if(it != mActors.end()){
        std::iter_swap(it, mActors.end() -1);
        mActors.pop_back();
    }
}

/* Private Methods */
void ConcreteScene::ProcessInput(){
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);

    for(auto actor : mActors){
        actor->ProcessInput(mWindow);
    }
    if(mCamera != nullptr)
        mCamera->ProcessInput(mWindow);
}

void ConcreteScene::AddDrawable(DrawComponent *drawable){
    mDrawables.emplace_back(drawable);
}

void ConcreteScene::RemoveDrawable(DrawComponent *drawable){
    auto it = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    if(it != mDrawables.end()){
        std::iter_swap(it, mDrawables.end() -1);
        mDrawables.pop_back();
    }
}


void ConcreteScene::RenderScene(){
    glClearColor(0x00, 0x00, 0x00, 0xFF);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto drawable : mDrawables){
        drawable->Draw();
    }
}

void ConcreteScene::UpdateScene(){
    
    float CurrentFrame = glfwGetTime();
    float DeltaTime = CurrentFrame - mLastFrame;
    mLastFrame = CurrentFrame;

    for(auto actor : mActors){
        actor->Update(DeltaTime);
    }
    if(mCamera != nullptr)
        mCamera->Update(DeltaTime);
    
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}