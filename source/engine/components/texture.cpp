#include "texture.h"

#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(Actor *owner, const std::string &filename, GLenum textureType):
    Component(owner),
    mTextureType(textureType)
{
    glGenTextures(1, &id);
    glBindTexture(textureType, id);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data = stbi_load(filename.c_str(), &mWidth, &mHeight, &mNumChannels, 0);

    if(data){
        glTexImage2D(textureType, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(textureType);
    } else{
        std::cerr << "Fail to load texture " << filename << "\n";
        exit(EXIT_FAILURE);
    }

    stbi_image_free(data);
}

Texture::~Texture(){
    glDeleteTextures(1, &id);
}

void Texture::bind(const GLint textureUnit){
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(mTextureType, id);
}