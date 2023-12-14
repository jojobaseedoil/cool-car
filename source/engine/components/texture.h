#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "component.h"

class Texture : Component{
public:
    Texture(Actor *owner, const std::string &filename, GLenum textureType=GL_TEXTURE_2D);
    ~Texture();

    void bind(const GLint textureUnit);

    GLuint id;

private:
    GLenum mTextureType;
    int mWidth, mHeight;
    int mNumChannels;
};