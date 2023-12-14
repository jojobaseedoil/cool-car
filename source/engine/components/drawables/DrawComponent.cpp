#include "DrawComponent.h"
#include "../../actors/actor.h"
#include "../../actors/camera.h"
#include "../../utils/OBJLoader.h"
#include "../material.h"


DrawComponent::DrawComponent(Actor *owner, const Vertex *vertices, const GLuint *indices, const GLuint nVertices, const GLuint nIndices, GLint DrawOrder):
    Component(owner),
    mMode(GL_TRIANGLES),
    mDrawOrder(DrawOrder)
{
    mOwner->GetScene()->AddDrawable(this);
    this->CreateBuffers(vertices, indices, nVertices, nIndices);
}

DrawComponent::DrawComponent(Actor *owner, const std::string &filename, const int DrawOrder):
    Component(owner),
    mMode(GL_TRIANGLES),
    mDrawOrder(DrawOrder)
{
    mOwner->GetScene()->AddDrawable(this);
    std::vector<Vertex> vertices = LoadObj(filename.c_str());
    this->CreateBuffers(vertices.data(), nullptr, vertices.size(), 0);
}

DrawComponent::~DrawComponent(){
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    if(mNumIndices > 0){
        glDeleteBuffers(1, &mEBO);
    }
}

void DrawComponent::CreateBuffers(const Vertex *vertices, const GLuint *indices, const GLuint nVertices, const GLuint nIndices){

    mNumVertices = nVertices;
    mNumIndices  = nIndices;

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mNumVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    if(mNumIndices > 0){
        glGenBuffers(1, &mEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
    }
    
    /* tell how gpu read position vertices */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    /* tell how gpu read color vertices */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    /* tell how gpu read texcoord vertices */
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    /* tell how gpu read normal vertices */
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}   

void DrawComponent::Draw(){

    InterfaceScene *scene = mOwner->GetScene();
    Shader program = scene->GetProgram();
    Camera *camera = mOwner->GetScene()->GetCamera();
    // Texture *texture = mOwner->GetComponent<Texture>();
    Texture *diffuse = mOwner->GetTextures()[0];
    Texture *specular = mOwner->GetTextures()[1];

    Material *material = mOwner->GetComponent<Material>();

    program.use();
    
    if(diffuse != nullptr)
        diffuse->bind(0);
    if(specular != nullptr)
        specular->bind(1);

    if(material != nullptr){
        material->sendToShader(&program);
    }

    /* Set up Matrices */
    program.SetMat4("model_matrix"      , mOwner->GetModel());
    program.SetMat4("view_matrix"       , camera->GetView());
    program.SetMat4("projection_matrix" , scene->GetProjection());

    /* Actually drawing */
    glBindVertexArray(mVAO);
    if(mNumIndices > 0){
        glDrawElements(mMode, mNumIndices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(mMode, 0, mNumVertices);
    }
}

void DrawComponent::SetDrawMode(const GLenum mode){
    mMode = mode;
}

void DrawComponent::SetWireFrame(bool WireFrameMode){
    if(WireFrameMode){
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    } else{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
}

const GLenum DrawComponent::GetDrawMode() const{
    return mMode;
}

const GLint DrawComponent::GetDrawOrder() const{
    return mDrawOrder;
}