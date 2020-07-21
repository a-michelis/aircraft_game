//
// Created by thele on 7/21/2020.
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

void Idle()
{
    // We could use timer function of gl, but this way we improve framerate on slower machines
    while (chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - t_begin).count() < 16666){}
    t_begin = chrono::steady_clock::now();

    // if either A or D is pressed
    if (tl ^ tr)
    {
        // If A (left) is pressed and rotation is not at max
        if (tl && KeyRot < 90.f)
        {
            KeyRot += 3.6f + (0.05f * (0.f - spd));
        }
            // If D (right) is pressed and rotation is not at max
        else if (tr && KeyRot > -90.f)
        {
            KeyRot += -3.6f - (0.05f * (0.f - spd));
        }
            // rotation is at (or close to) max
        else
        {
            KeyRot = (abs(KeyRot)/KeyRot)*90.f;
        }
    }
    // else, if no or both direction keys are pressed and rotation isn't zero
    else if (KeyRot != 0)
    {
        // bring smoothly the rotation base variable back to zero
        if (KeyRot > 2.8)
        {
            KeyRot = KeyRot - 2.8f;
        }
        else if (KeyRot < -2.8)
        {
            KeyRot = KeyRot + 2.8f;
        }
        else
        {
            KeyRot = 0;
        }
    }

    // If W or S is pressed
    if (f ^ s)
    {
        // if W (faster) is pressed and we dont exceed our upper bound
        if (f && spd > -25)
        {
            spd -= 0.5;
        }
        // if W (slower) is pressed and we dont exceed our lower bound
        else if (s && spd < -3)
        {
            spd += 0.5;
        }
    }

    // Our (new) direction corresponds to the speed we're going,
    // as well as our current rotation... It wraps around [0,360)...
    dir = fmod(360.f + (dir - KeyRot/(100.f + (spd + 12.f) * 2.5f)), 360.f);

    // We calculate our new light position, according to our direction.
    lightPos[0] = cos(dir * (2* M_PI) / 360)*100;
    lightPos[2] = sin(dir * (2* M_PI) / 360)*100 -90.f;

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // We recalculate our direction vector...
    TERA->CalcDirection(0.f - dir);
    // And redraw our map to match our new position (we moved spd/10 since last time)...
    TERA->GenTerrain(spd/10);

    // Z-Rotation is the rotation done to the aircraft, when it turns left/right.
    zrot =60.f*(float)sin(KeyRot * 2 * M_PI / 360);

    // (Y-)Rotation is the slight rotation done to the aircraft to better represent turning
    rot = 0.5f*zrot;

    // both flaps must X-Rotate themselves and move to remain connected to the aircraft's winds.
    w1r = w2r = -0.5f * rot;

    w1m = (float)sin(w1r / (360/(2*M_PI)));
    w1b =  (float)cos(w2r / (360/(2*M_PI)));

    w2m = (float)sin(w1r / (360/(2*M_PI)));
    w2b =  (float)cos(w2r / (360/(2*M_PI)));

    // Propeler must rotate the whole time (the rotation speed corresponds to the speed of the aircraft)
    elikas = fmod(elikas + (10-(1.5*spd)), 360);

    // This is just a "clock divider" so we won't flood our console with dbg messages.
    if((dbgf = (dbgf+1)%10)==0) dbg();

    // Finally, we reDraw our screen.
    glutPostRedisplay();
}