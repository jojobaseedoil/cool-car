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
	VIEW
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
    inline GLint GetLocation(const std::string &name) const{
        return glGetUniformLocation(id, name.c_str());
    }
    inline void SetBool(const std::string &name, bool value) const{
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }
    inline void SetInt(const std::string &name, int value) const{
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }
    inline void SetFloat(const std::string &name, float value) const{
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }
    inline void SetColor(const std::string &name, GLfloat *color) const{
        glUniform3fv(Location::COLOR, 1, color);
    }
    inline void SetProjection(const std::string &name, const glm::mat4 &projection) const{ /* set projection matrix */
        glUniformMatrix4fv(Location::PROJECTION, 1, GL_FALSE, glm::value_ptr(projection));
    }
    inline void SetView(const std::string &name, const glm::mat4 &view) const{ /* set view matrix */
        glUniformMatrix4fv(Location::VIEW, 1, GL_FALSE, glm::value_ptr(view));
    }
    inline void SetModel(const std::string &name, const glm::mat4 &model) const{ /* set model matrix */
        glUniformMatrix4fv(Location::MODEL, 1, GL_FALSE, glm::value_ptr(model));
    }
};