//
// Created by thele on 7/18/2020.
//

#include <iostream>
#include <cmath>
#include "../gameEngine/gameEngine.h"

float rot = 0.f;
float elikas = 0.f;
float forReal = 0.f;

void Idle()
{
    forReal = fmod(forReal + 0.36, 360);
    rot =45*sin(forReal * 2 * M_PI /  360);
    elikas = fmod(elikas + 12, 360);

    glutPostRedisplay();
}




void Close()
{
}