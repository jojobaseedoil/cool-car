#include "material.h"

Material::Material(        
    Actor *owner,
    const glm::vec3 &ambient,
    const glm::vec3 &diffuse,
    const glm::vec3 &specular,
    GLint diffuseTexture,
    GLint specularTexture 
):
    Component(owner),
    mAmbient(ambient),
    mDiffuse(diffuse),
    mSpecular(specular),
    mDiffuseTexture(diffuseTexture),
    mSpecularTexture(specularTexture)
{

}

void Material::sendToShader(Shader *program){
    program->SetVec3f("material.ambient"        , mAmbient);    
    program->SetVec3f("material.diffuse"        , mDiffuse);    
    program->SetVec3f("material.specular"       , mSpecular);    
    program->SetInt("material.diffuse_texture"  , mDiffuseTexture);
    program->SetInt("material.specular_texture" , mSpecularTexture );
}