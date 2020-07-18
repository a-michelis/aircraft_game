//
// Created by thele on 7/19/2020.
//

#include "../gameEngine/gameEngine.h"

bool tl = false;
bool tr = false;

void KeyDown(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a':
            tl = true;
            break;
        case 'd':
            tr = true;
            break;
    }
}
void KeyUp(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a':
            tl = false;
            break;
        case 'd':
            tr = false;
            break;
    }
}