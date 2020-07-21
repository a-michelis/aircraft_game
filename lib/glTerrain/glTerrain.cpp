//
// Created by thele on 7/19/2020.
//

#include <cmath>
#include <iostream>
#include "../gameEngine/gameEngine.h"


glTerrain::glTerrain(int size, float actualsize, float y_min, float y_max, float pitch, vec2f **texture_bounds, const char **textures, int texCount) {
    randRange rnd(-1.f, 1.f);
    Direction = new vec2f(0, 1);
    _size = size+1;
    _actualsize = actualsize;
    _pitch = pitch;
    _max = y_max;
    _min = y_min;

    _NoiseMap = new float*[_size];
    _HeightMap = new float*[_size];

    for (int i = 0; i < _size; i++)
    {
        _HeightMap[i] = new float[_size];
        _NoiseMap[i] = new float[_size];

        for(int j = 0; j < _size; j++) _NoiseMap[i][j] = rnd();
    }
    _texCount = texCount;
    if (texCount > 0)
    {
        _texCount = texCount;
        _texture_bounds = new vec2f*[texCount];
        _textures = new string*[texCount];
        for(int i = 0; i < texCount; i++)
        {
            _texture_bounds[i] = new vec2f(texture_bounds[i]->x, texture_bounds[i]->y);
            _textures[i] = new string(textures[i]);
        }
    }
    else{
        cout << "Error: No texture selected for the terrain" << endl;
        exit(-1);
    }
}

void glTerrain::DrawModel(float resolution) {

    
    
    
    auto *tid = new GLuint[_texCount];
    for (int i = 0; i < _texCount; i++) tid[i] = gameEngine::GetTexture(_textures[i]->c_str());

    float q = resolution <= 0.f ? 0.1f : resolution;
    float r = (float)_size/(_actualsize);

    glEnable(GL_TEXTURE_2D);
    for (int i = 1; i < _size; i++)
    {
        glDisable(GL_BLEND);
        glBindTexture(GL_TEXTURE_2D, tid[0]);

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < _size; j++)
        {
            //TerrainColor(_HeightMap[i][j]);
            glTexCoord2f(q*r*(float)i + q*Position->x*2,  q*r*(float)j + q*Position->y*2);
            glVertex3f((float)i * (_actualsize/(float)(_size - 1)), _HeightMap[i][j], (float)j * (_actualsize/(float)(_size - 1)));

            //TerrainColor(_HeightMap[i-1][j]);
            glTexCoord2f(q*r*(float)(i-1) + q*Position->x*2, q*r*(float)j + q*Position->y*2);
            glVertex3f((float)(i-1) * (_actualsize/(float)(_size - 1)), _HeightMap[i-1][j], (float)j * (_actualsize/(float)(_size - 1)));
        }
        glEnd();

        glEnable(GL_BLEND);



        for(int k = 1; k < _texCount; k++)
        {
            glBindTexture(GL_TEXTURE_2D, tid[k]);
            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j < _size; j++)
            {
                float h1 = (_HeightMap[i][j] - _min)/(_max - _min);
                float h2 = (_HeightMap[i-1][j] - _min)/(_max - _min);

                glColor4f(1,1,1, h1 < _texture_bounds[k]->x ? 0 : (h1 > _texture_bounds[k]->y ? 0 : 1));
                glTexCoord2f(q*r*(float)i + q*Position->x*2,  q*r*(float)j + q*Position->y*2);
                glVertex3f((float)i * (_actualsize/(float)(_size - 1)), _HeightMap[i][j], (float)j * (_actualsize/(float)(_size - 1)));

                //TerrainColor(_HeightMap[i-1][j]);
                glColor4f(1,1,1, h2 < _texture_bounds[k]->x ? 0 : (h2 > _texture_bounds[k]->y ? 0 : 1));
                glTexCoord2f(q*r*(float)(i-1) + q*Position->x*2, q*r*(float)j + q*Position->y*2);
                glVertex3f((float)(i-1) * (_actualsize/(float)(_size - 1)), _HeightMap[i-1][j], (float)j * (_actualsize/(float)(_size - 1)));
            }
            glEnd();
        }
    }
    glDisable(GL_TEXTURE_2D);
}

void glTerrain::CalcDirection(float angle)
{
    // cos = z
    // sin = x
    auto x = (float)sin(angle * (2*M_PI)/360.f);
    auto z = (float)cos(angle * (2*M_PI)/360.f);
    Direction = new vec2f(x, z);

}

void glTerrain::GenTerrain(float speed) {

    float newx = fmod(Position->x + (_pitch * speed * Direction->x), _size);
    newx = newx < 0 ? newx + (float)_size : newx;

    float newy = fmod(Position->y + (_pitch * speed * Direction->y), _size);
    newy = newy < 0 ? newy + (float)_size : newy;

    Position = new vec2f(
            newx,
            newy
            );

    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {

            float res = noise((float)i,(float)j, _pitch);
            //res += 0.1 * noise(i,j, _pitch * 10);
            res += 0.04f * noise((float)i,(float)j, 0.117f + _pitch * 7);
            res /= 1.04f;
            res = res * (_max - _min) + _min;
            _HeightMap[i][j] = res < _min ? _min : res;
        }
    }
}

float glTerrain::noise(float i, float j, float pitch)
{
    int prvi = (int)floor((float)_size + Position->x + (i * _pitch)) % _size;
    int nxti = (int)ceil((float)_size + Position->x + (i * _pitch)) % _size;
    int prvj = (int)floor((float)_size + Position->y + (j * _pitch)) % _size;
    int nxtj = (int)ceil((float)_size + Position->y + (j * _pitch)) % _size;


    double q[4] = {
            _NoiseMap[prvi][prvj],
            _NoiseMap[nxti][prvj],
            _NoiseMap[nxti][nxtj],
            _NoiseMap[prvi][nxtj]
    };

    double blendi= 1 - cos(fmod(((float)_size + Position->x + (i * pitch)), 1.f) * (M_PI/2.f));
    double blendj= 1 - cos(fmod(((float)_size + Position->y + (j * pitch)), 1.f) * (M_PI/2.f));

    double res = blendi * (q[2] * blendj + q[1] * (1-blendj)) + (1-blendi) * (q[3] * blendj + q[0] * (1-blendj));
    return (float)res;
}