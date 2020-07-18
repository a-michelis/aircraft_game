//
// Created by thele on 7/18/2020.
//

#include "../gameEngine/gameEngine.h"

void Resize(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // Setup viewing volume

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //gluPerspective(90, (float) w / (float) h, 1, 1000);
    gluPerspective(60, (float) w / (float) h, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}