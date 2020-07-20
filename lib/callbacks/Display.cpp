//
// Created by thele on 7/18/2020.
//


#include <iostream>
#include "../gameEngine/gameEngine.h"

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(10, 1, 0, 0);
    glTranslatef(0,-20, 0);
    glPushMatrix();
    gameEngine::DrawModels();
    glPopMatrix();

    glPushMatrix();

        glRotatef(dir, 0,1,0);
        glTranslatef(-800,-200, -800);

        TERA->DrawModel(0.5);
    glPopMatrix();

    glutSwapBuffers();
}