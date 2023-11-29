cmake_minimum_required(VERSION 3.0.0) # cmake minimum version to build this project
project(MyCar VERSION 0.1.0) # define project name

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED) # make opengl a dependence of this project. REQUIRED raises an error if something goes wrong.

add_executable(
	MyCar

    # ENGINE SPECIFICS
    source/engine/DrawableObject.cpp
    source/engine/ConcreteScene.cpp
    source/engine/shader.cpp
    source/engine/camera.cpp
    
    # ADD SCENES SPECIFICS HERE  
    source/scenes/CarScene.cpp

    # MAIN FILE
    source/main.cpp
)

# add a new subdirectory with glad functions
add_subdirectory(source/utils/glad)
target_link_libraries(${PROJECT_NAME} glad) # this project depends on glad

# do the same for glm - math library
option(BUILD_SHARED_LIBS "Build shared library" ON)
add_subdirectory(source/utils/glm)
target_link_libraries(${PROJECT_NAME} glm) # this project depends on glm

target_link_libraries(MyCar glfw OpenGL::GL) # this project depends on glfw and opengl