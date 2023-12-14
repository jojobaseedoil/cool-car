/*
    This code is from learnopengl website:
    https://learnopengl.com/
*/
#pragma once

#include "../utils/glad/include/glad/glad.h"
#include "../utils/glm/glm.hpp"
#include "../utils/glm/ext.hpp"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>

#define VERTEX_SHADER_PATH "../source/shaders/shader.vs"
#define FRAGMENT_SHADER_PATH "../source/shaders/shader.fs"

/* Layout location at shader program */
enum Location : GLuint{
	POSITION,
	COLOR,
	PROJECTION,
	MODEL,
	VIEW,
    TEXCOORD
};

class Shader{
public:
    /* build and read shaders */
    Shader() = default;
    Shader(const char *VertexShaderPath, const char *FragmentShaderPath);
    
    /* Program id */
    GLuint id;

    /* Activate shader */
    inline void use(){ glUseProgram(id); }

    /* utility uniform functions */
    void SetBool(const std::string &name, const bool value) const;
    void SetInt(const std::string &name, const int value) const;
    void SetFloat(const std::string &name, const float value) const;
    void SetMat4(const std::string &name, const glm::mat4 &value) const;
    void SetVec3f(const std::string &name, const glm::vec3 &value) const;
};