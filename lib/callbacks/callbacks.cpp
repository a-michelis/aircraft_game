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
float spd = -3.f;

float elikas = 0.f;
int dbgf = 0;

chrono::steady_clock::time_point t_begin;

void dbg();

void Idle()
{

    while (chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - t_begin).count() < 16666){}
    t_begin = chrono::steady_clock::now();


    if (!(tl ^ tr)) {
        KeyRot = KeyRot > 0 ? KeyRot - 2.8 : (KeyRot < 0 ? KeyRot + 2.8 : 0);
        if (KeyRot < 2.8 && KeyRot > -2.8) KeyRot = 0;
    }
    else
    {
        KeyRot += tl ? 3.6 + (0.05 * (0-spd)) : -3.6 - (0.05 * (0-spd));
        KeyRot = KeyRot > 90 ? 90 : (KeyRot < -90  ? -90 : KeyRot);
    }

    if ((f ^ s))
    {
        spd += f ? -0.5 : 0.5;
        spd = spd < -25 ? -25 : (spd > -3 ? -3 : spd);
    }

    dir -= KeyRot/100.f;
    if (dir < - 360) dir += 360;
    if (dir > 360) dir -= 360;

    //cout << "Direction: " << dir << endl;
    lightPos[0] = cos(dir * (2* M_PI) / 360)*100;
    lightPos[2] = sin(dir * (2* M_PI) / 360)*100 -90.f;

    //glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);

    TERA->CalcDirection(0.f - dir);
    TERA->GenTerrain(spd/10);

    zrot =60*sin(KeyRot * 2 * M_PI / 360);

    rot = 0.5*zrot;

    w1r = w2r = -0.5 * rot;

    w1m = sin(w1r / (360/(2*M_PI)));
    w2m = sin(w1r / (360/(2*M_PI)));

    w1b =  cos(w2r / (360/(2*M_PI)));
    w2b =  cos(w2r / (360/(2*M_PI)));

    elikas = fmod(elikas + (10-(1.5*spd)), 360);


    dbgf = (dbgf+1)%10;
    if(dbgf==0) dbg();

    glutPostRedisplay();
}

void dbg()
{
    cout << "DBG:\t\tPosition -> [" << TERA->Position->x << ", " << TERA->Position->y << "]" << endl;
    cout << "\t\t\tDirection -> [X:" << TERA->Direction->x << ", Z:" << TERA->Direction->y << "]" << endl;
    cout << endl;
}



void Close()
{
    gameEngine::RemoveAllModels();
    gameEngine::RemoveAllTextures();
}