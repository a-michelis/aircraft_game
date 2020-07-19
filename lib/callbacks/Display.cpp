//
// Created by thele on 7/18/2020.
//


#include <iostream>
#include "../gameEngine/gameEngine.h"

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(30, 1, 0, 0);
    glTranslatef(0,-120, 0);
    gameEngine::DrawModels();

    glPushMatrix();
    glRotatef(dir, 0,1,0);
    glTranslatef(-800,-200, -800);
    glBegin(GL_TRIANGLE_STRIP);
    //glColor4f(0,1,1,1);
    //cout << gluErrorString(glGetError()) << endl;
    TERA->DrawModel();
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}