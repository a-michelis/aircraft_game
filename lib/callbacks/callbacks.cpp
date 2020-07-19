//
// Created by thele on 7/18/2020.
//

#include <iostream>
#include <cmath>
#include "../gameEngine/gameEngine.h"

float KeyRot = 0.f;
float dir = 0.f;
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
        KeyRot = KeyRot > 0 ? KeyRot - 0.72 : (KeyRot < 0 ? KeyRot + 0.72 : 0);
        if (KeyRot < 0.72 && KeyRot > -0.72) KeyRot = 0;
    }
    else
    {
        KeyRot += tl ? 1.44 : -1.44;
        KeyRot = KeyRot > 90 ? 90 : (KeyRot < -90 ? -90 : KeyRot);
    }

    dir -= KeyRot/100.f;
    if (dir < - 360) dir += 360;
    if (dir > 360) dir -= 360;

    //cout << "Direction: " << dir << endl;

    TERA->CalcDirection(0.f - dir);
    TERA->GenTerrain(-0.5);

    zrot =60*sin(KeyRot * 2 * M_PI / 360);

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