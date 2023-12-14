#include "CarScene.h"
#include "../engine/actors/camera.h"
#include "../engine/actors/car.h"
#include "../engine/components/drawables/DrawComponent.h"
#include "../engine/actors/light.h"
#include "../engine/actors/floor.h"
#include "../engine/actors/StaticActor.h"
#include "../engine/components/material.h"
#include "../engine/components/RigidBodyComponent.h"

CarScene::CarScene(GLint WindowWidth, GLint WindowHeight):
    ConcreteScene(WindowWidth, WindowHeight),
    mLight(nullptr)
{

}

void CarScene::CreateScene(){

    const glm::vec3 eye(0,0,5);
    const glm::vec3 center(0,0,-1);
    const glm::vec3 up(0,1,0);
    mCamera = new Camera(this,eye,center,up);
    // SetOrtho(-20,20,-20,20,-50,50);
    SetPerspective(90.0f, (float)(mWindowWidth)/mWindowHeight, 0.1f, 5000.0f);
    
    Light *light = new Light(this);
    light->SetPosition(glm::vec3(0,0,5));

    const Vertex vertices[] = {
        /* position */                  /* color */                     /* texcoord */              /* normal */
        glm::vec3(-0.5f,0.5f,0.0f),     glm::vec3(1.0f,0.0f,0.0f),      glm::vec2(0.0f,1.0f),       glm::vec3(0.0f,0.0f,1.0f),
        glm::vec3(-0.5f,-0.5f,0.0f),    glm::vec3(0.0f,1.0f,0.0f),      glm::vec2(0.0f,0.0f),       glm::vec3(0.0f,0.0f,1.0f),
        glm::vec3(0.5f,-0.5f,0.0f),     glm::vec3(0.0f,0.0f,1.0f),      glm::vec2(1.0f,0.0f),       glm::vec3(0.0f,0.0f,1.0f),
        glm::vec3(0.5f,0.5f,0.0f),      glm::vec3(1.0f,1.0f,0.0f),      glm::vec2(1.0f,1.0f),       glm::vec3(0.0f,0.0f,1.0f)
    };
    const unsigned int numVertices = sizeof(vertices) / sizeof(Vertex);

    const GLuint indices[] = {
        0, 1, 2, // triangle1
        0, 2, 3  // triangle2
    };
    const unsigned int numIndices = sizeof(indices) / sizeof(GLuint);
    
    const glm::vec3 ambient(0.1f);
    const glm::vec3 diffuse(1.f);
    const glm::vec3 specular(1.f);
    const GLint diffuseTexture  = 0;
    const GLint specularTexture = 0;

    StaticActor *floor = new StaticActor(this);
    Texture *floorTex = new Texture(floor, "../models/lua.jpeg", GL_TEXTURE_2D);
    floor->SetTextures(floorTex, floorTex);
    new Material(floor, ambient, diffuse, specular, diffuseTexture, specularTexture);
    new DrawComponent(floor, vertices, indices, numVertices, numIndices);
    floor->SetPosition(glm::vec3(0,0,-2));
    floor->SetScale(glm::vec3(1000,1000,1));
    
    mCar = new Car(this);
    Texture *base = new Texture(mCar, "../models/Vazz_Car_Big_Parts_BaseColor.png");
    Texture *metallic = new Texture(mCar, "../models/Vazz_Car_Big_Parts_Metallic.png");
    mCar->SetTextures(base, metallic);

    new Material(mCar, ambient, diffuse, specular, diffuseTexture, specularTexture);
    new DrawComponent(mCar, "../models/fusca.obj");
    new RigidBodyComponent(mCar, 1, 4);
    mCar->SetRotation(glm::vec3(90.0f,0.0f,0.0f));
    mCar->SetScale(glm::vec3(3,3,3));

    for(int i=0; i<10; i++){
        StaticActor *tree = new StaticActor(this);
        new DrawComponent(tree, "../models/pine.obj");
        Texture *treeTex = new Texture(tree, "../models/pine.jpg");
        tree->SetTextures(treeTex, treeTex);
        tree->SetPosition(glm::vec3( 100, i*100, -2.0f ));
        tree->SetScale(glm::vec3(0.25, 0.25, 0.25));
        tree->SetRotation(glm::vec3(0,0,90));
    
        StaticActor *tree1 = new StaticActor(this);
        new DrawComponent(tree1, "../models/pine.obj");
        tree1->SetTextures(treeTex, treeTex);
        tree1->SetPosition(glm::vec3( -100, i*100, -2.0f ));
        tree1->SetScale(glm::vec3(0.25, 0.25, 0.25));
        tree1->SetRotation(glm::vec3(0,0,90));

    }



    StaticActor *skybox = new StaticActor(this);
    new DrawComponent(skybox, "../models/ceuzao.obj");
    Texture *skytex = new Texture(skybox, "../models/stars.jpg");
    skybox->SetTextures(skytex, skytex);

    skybox->SetScale(glm::vec3(-25, -25, -25));
    skybox->SetRotation(glm::vec3(0,0,90));

    // for(int i=0; i<10; i++){
    //     StaticActor *grass = new StaticActor(this);
    //     new DrawComponent(grass, "../models/camelia.obj");
    //     new Texture(grass, "../models/camelia.jpg");
    //     grass->SetPosition(glm::vec3( rand()%500, rand()%500, -1.0f ));
    //     grass->SetScale(glm::vec3(0.1, 0.1, 0.1));
    // }
}