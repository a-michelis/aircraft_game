//
// Created by thele on 7/18/2020.
//

#ifndef AIRCRAFT_GAME_CALLBACKS_H
#define AIRCRAFT_GAME_CALLBACKS_H

#include "../gameEngine/gameEngine.h"

extern float rot;
extern float elikas;
extern float zrot;
extern float w1m;
extern float w2m;
extern float w1b;
extern float w2b;
extern float w1r;
extern float w2r;

void Display();
void Resize(int w, int h);
void Idle();

void Setup();
void Close();



#endif //AIRCRAFT_GAME_CALLBACKS_H
