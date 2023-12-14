#include "floor.h"
#include "../../utils/libs.h"
#include "../components/drawables/DrawComponent.h"
#include "../components/texture.h"
#include "../components/material.h"

Floor::Floor(InterfaceScene *scene):
    Actor(scene)
{
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

    new DrawComponent(this, vertices, indices, numVertices, numIndices);
    new Texture(this, "../models/circuit.jpg", GL_TEXTURE_2D, GL_TEXTURE11);

    const glm::vec3 ambient(0.5f);
    const glm::vec3 diffuse(1.f);
    const glm::vec3 specular(1.f);
    const GLint diffuseTexture  = 1;
    const GLint specularTexture = 1;
    new Material(this, ambient, diffuse, specular, diffuseTexture, specularTexture);

    SetPosition(glm::vec3(0,0,-2));
    SetScale(glm::vec3(1000,1000,1));
}

void Floor::OnUpdate(float DeltaTime){
    mModelMatrix = glm::mat4(1.f);
    mModelMatrix = glm::translate(mModelMatrix, mPosition);
    mModelMatrix = glm::scale(mModelMatrix, mScale);
}