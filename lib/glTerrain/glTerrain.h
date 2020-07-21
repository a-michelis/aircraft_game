//
// Created by thele on 7/19/2020.
//

#ifndef AIRCRAFT_GAME_GLTERRAIN_H
#define AIRCRAFT_GAME_GLTERRAIN_H


#include "../gameEngine/gameEngine.h"

class glTerrain {
    float ** _HeightMap;
    float ** _NoiseMap;
    int _size;
    float _actualsize;
    float _pitch;
    float _min, _max;
    vec2f **_texture_bounds = nullptr;
    string **_textures = nullptr;
    int _texCount = 0;




public:
    vec2f *Position = new vec2f (0, 0);
    vec2f *Direction = new vec2f(0, 1);

    glTerrain(int size, float actualsize, float y_min, float y_max, float pitch, vec2f **texture_bounds, const char **textures, int texCount = 0);
    void DrawModel(float resolution);
    void CalcDirection(float angle);
    void GenTerrain(float speed);

private:
    float noise(float i, float j, float pitch);
};


#endif //AIRCRAFT_GAME_GLTERRAIN_H
