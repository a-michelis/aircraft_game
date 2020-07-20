#include <iostream>
#include "lib/gameEngine/gameEngine.h"

int main(int argc, char *argv[]) {

    cout << "Aircraft Game!" << endl;
    cout << "Michelis Andreas [2022 2013 00097]" << endl;
    cout << endl;
    cout << "Controls:" << endl;
    cout << "\tW: Speed up" << endl;
    cout << "\tA: Turn left" << endl;
    cout << "\tS: Slow down" << endl;
    cout << "\tD: Turn right" << endl;
    cout << endl;
    cout << "Press ENTER to continue..." << endl;
    cin.get();

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


    gameEngine::StartLoop();


    return 0;
}

