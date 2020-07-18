//
// Created by thele on 7/18/2020.
//

#include <iostream>
#include <cmath>
#include "../gameEngine/gameEngine.h"

float forReal = 0.f;
float rot = 0.f;
float zrot = 0.f;
float w1m = 0.f;
float w2m = 0.f;
float w1b = 0.f;
float w2b = 0.f;
float w1r = 0.f;
float w2r = 0.f;

float elikas = 0.f;

void Idle()
{
    if (!(tl ^ tr)) {
        forReal = forReal > 0 ? forReal - 0.72 : (forReal < 0 ? forReal + 0.72 : 0);
        if (forReal < 0.72 && forReal > -0.72) forReal = 0;
    }
    else
    {
        forReal += tl ? 0.72 : -0.72;
        forReal = forReal > 90 ? 90 : (forReal < -90 ? -90 : forReal);
    }

    zrot =60*sin(forReal * 2 * M_PI /  360);
    //float qq =80*sin(forReal * 2 * M_PI /  360);
    rot = 0.5*zrot;

    w1r = w2r = -0.5 * rot;

    w1m = sin(w1r / (360/(2*M_PI)));
    w2m = sin(w1r / (360/(2*M_PI)));

    w1b =  cos(w2r / (360/(2*M_PI)));
    w2b =  cos(w2r / (360/(2*M_PI)));

    elikas = fmod(elikas + 12, 360);

    glutPostRedisplay();
}




void Close()
{
}