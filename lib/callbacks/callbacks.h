//
// Created by thele on 7/18/2020.
//

#ifndef AIRCRAFT_GAME_CALLBACKS_H
#define AIRCRAFT_GAME_CALLBACKS_H

#include "../gameEngine/gameEngine.h"

extern float rot;
extern float elikas;

void Display();
void Resize(int w, int h);
void Idle();

void Setup();
void Close();



#endif //AIRCRAFT_GAME_CALLBACKS_H
