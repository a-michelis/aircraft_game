//
// Created by thele on 7/19/2020.
//

#include <iostream>
#include "../gameEngine/gameEngine.h"

bool tl = false;
bool tr = false;
bool f = false;
bool s = false;

void KeyDown(unsigned char key, int x, int y)
{
    //cout << "Key Pressed: " << (int)key << endl;

    key = tolower(key);
    switch (key) {
        case 'a':
            tl = true;
            break;
        case 'd':
            tr = true;
            break;
        case 'w':
            f = true;
            break;
        case 's':
            s = true;
            break;
        default:
            break;
    }
}
void KeyUp(unsigned char key, int x, int y)
{
    key = tolower(key);
    switch (key) {
        case 'a':
            tl = false;
            break;
        case 'd':
            tr = false;
            break;
        case 'w':
            f = false;
            break;
        case 's':
            s = false;
            break;
        default:
            break;
    }
}