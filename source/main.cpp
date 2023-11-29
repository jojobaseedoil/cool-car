#include "scenes/CarScene.h"

const GLint SCREEN_WIDTH = 800;
const GLint SCREEN_HEIGHT = 600;

int main(int argc, char **argv){

    CarScene MyScene(SCREEN_WIDTH, SCREEN_HEIGHT);
    bool Success = MyScene.StartScene();
    if(Success){
        MyScene.MainLoop();
    }
    MyScene.EndScene();

    return 0;
}