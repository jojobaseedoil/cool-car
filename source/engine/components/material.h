#pragma once

#include "component.h"

class Shader;

class Material : public Component{
public:
    Material(
        Actor *owner,
        const glm::vec3 &ambient,
        const glm::vec3 &diffuse,
        const glm::vec3 &specular,
        GLint diffuseTexture,
        GLint specularTexture 
    );

    void sendToShader(Shader *program);

private:
    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;
    GLint mDiffuseTexture;
    GLint mSpecularTexture;
};