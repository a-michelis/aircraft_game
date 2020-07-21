//
// Created by thele on 7/21/2020.
//

#ifndef AIRCRAFT_GAME_RANDRANGE_H
#define AIRCRAFT_GAME_RANDRANGE_H

#include <random>

class randRange {
    double a, b;
public:
    randRange(float lower, float upper)
    {
        a = lower; b = upper;
        srand(time(nullptr));
    }

    float operator()() {
        return ((double)rand() / (double)RAND_MAX) * (b - a) + a;
    }
};


#endif //AIRCRAFT_GAME_RANDRANGE_H
