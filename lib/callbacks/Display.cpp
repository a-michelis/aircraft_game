//
// Created by thele on 7/18/2020.
//


#include "../gameEngine/gameEngine.h"

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(30, 1, 0, 0);
    glTranslatef(0,-120, 0);
    gameEngine::DrawModels();

    glutSwapBuffers();
}