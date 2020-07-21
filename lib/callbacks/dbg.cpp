//
// Created by thele on 7/18/2020.
//

#include <iostream>
#include "../gameEngine/gameEngine.h"

void dbg()
{
    cout << "DBG:        Position -> [" << TERA->Position->x << ", " << TERA->Position->y << "]" << endl;
    cout << "            Direction -> [X:" << TERA->Direction->x << ", Z:" << TERA->Direction->y << "]" << endl;
    cout << endl;
}