/*
    This code is from learnopengl website:
    https://learnopengl.com/
*/
#include "shader.h"

Shader::Shader(const char*VertexShaderPath, const char*FragmentShaderPath){
    
    // retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        // open files
        vShaderFile.open(VertexShaderPath);
        fShaderFile.open(FragmentShaderPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure&e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // === VERTEX SHADER ===
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
        exit(EXIT_FAILURE);
    };

    // == FRAGMENT SHADER ===
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
        exit(EXIT_FAILURE);
    };

    // shader Program
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    // print linking errors if any
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(this->id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
        infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    // delete shaders; no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::SetBool(const std::string &name, const bool value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetInt(const std::string &name, const int value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, const float value) const{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetMat4(const std::string &name, const glm::mat4&value) const{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3f(const std::string &name, const glm::vec3 &value) const{
    glUniform3fv(glGetUniformLocation(this->id, name.c_str()), 1, glm::value_ptr(value));
}