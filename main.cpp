#include <iostream>
#include "lib/gameEngine/gameEngine.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    gameEngine::Init(
            new vec2(40, 40),
            new vec2(600, 600),
            "2nd Example",
            new unsigned int[3]{GLUT_DEPTH, GLUT_DOUBLE, GLUT_RGBA}, 3,
            &argc, argv
            );
    gameEngine::SetupCallback(Setup);
    gameEngine::CloseCallback(Close);

    gameEngine::DisplayCallback(Display);
    gameEngine::ResizeCallback(Resize);
    gameEngine::IdleCallback(Idle);
    gameEngine::KeyDownCallback(KeyDown);
    gameEngine::KeyUpCallback(KeyUp);

    //glutErrorFunc()

    gameEngine::StartLoop();


    return 0;
}

