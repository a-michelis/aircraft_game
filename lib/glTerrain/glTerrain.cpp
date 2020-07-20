//
// Created by thele on 7/19/2020.
//

#include <cmath>
#include "../gameEngine/gameEngine.h"
#include "glTerrain.h"


glTerrain::glTerrain(int size, float actualsize, float y_min, float y_max, float pitch, float *col_bounds, vec3f **cols, int colCount) {
    srand(NULL);

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

        for(int j = 0; j < _size; j++) _NoiseMap[i][j] = RandRange(-1,1);
    }

    if (colCount > 0)
    {
        _colorCount = colCount;
        _color_bounds = new float[colCount];
        _colors = new vec3f*[colCount];
        for(int i = 0; i < colCount; i++)
        {
            _color_bounds[i] = col_bounds[i];
            _colors[i] = new vec3f(cols[i]);
        }
    }
    else{
        _colorCount = 2;
        _color_bounds = new float[2]{0,1};
        _colors = new vec3f*[2]{new vec3f(0,0,0), new vec3f(1,1,1)};
    }
}

void glTerrain::DrawModel(float resolution) {

    GLuint tid[3] = {
            gameEngine::GetTexture("low"),
            gameEngine::GetTexture("mid"),
            gameEngine::GetTexture("high")
    };
    float q = resolution <= 0.f ? 0.1f : resolution;
    float r = (float)_size/(_actualsize);
    glEnable(GL_TEXTURE_2D);
    for (int i = 1; i < _size; i++)
    {
        glDisable(GL_BLEND);

        glBindTexture(GL_TEXTURE_2D, tid[1]);

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < _size; j++)
        {
            //TerrainColor(_HeightMap[i][j]);
            glTexCoord2f(q*r*i + q*Position->x*2,  q*r*j + q*Position->y*2);
            glVertex3f((float)i * (_actualsize/(float)(_size - 1)), _HeightMap[i][j], (float)j * (_actualsize/(float)(_size - 1)));

            //TerrainColor(_HeightMap[i-1][j]);
            glTexCoord2f(q*r*(i-1) + q*Position->x*2, q*r*j + q*Position->y*2);
            glVertex3f((float)(i-1) * (_actualsize/(float)(_size - 1)), _HeightMap[i-1][j], (float)j * (_actualsize/(float)(_size - 1)));
        }
        glEnd();

        glEnable(GL_BLEND);

        glBindTexture(GL_TEXTURE_2D, tid[0]);
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < _size; j++)
        {
            //TerrainColor(_HeightMap[i][j]);
            glColor4f(1,1,1, _HeightMap[i][j] <= 1 ? 1 : 0);
            glTexCoord2f(q*r*i + q*Position->x*2,  q*r*j + q*Position->y*2);
            glVertex3f((float)i * (_actualsize/(float)(_size - 1)), _HeightMap[i][j], (float)j * (_actualsize/(float)(_size - 1)));

            //TerrainColor(_HeightMap[i-1][j]);
            glColor4f(1,1,1, _HeightMap[i-1][j] <= 1 ? 1 : 0);
            glTexCoord2f(q*r*(i-1) + q*Position->x*2, q*r*j + q*Position->y*2);
            glVertex3f((float)(i-1) * (_actualsize/(float)(_size - 1)), _HeightMap[i-1][j], (float)j * (_actualsize/(float)(_size - 1)));
        }
        glEnd();

        glBindTexture(GL_TEXTURE_2D, tid[2]);
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < _size; j++)
        {
            //TerrainColor(_HeightMap[i][j]);
            glColor4f(1,1,1, _HeightMap[i][j] >= 55 ? 1 : 0);
            glTexCoord2f(q*r*i + q*Position->x*2,  q*r*j + q*Position->y*2);
            glVertex3f((float)i * (_actualsize/(float)(_size - 1)), _HeightMap[i][j], (float)j * (_actualsize/(float)(_size - 1)));

            //TerrainColor(_HeightMap[i-1][j]);
            glColor4f(1,1,1, _HeightMap[i-1][j] >= 55 ? 1 : 0);
            glTexCoord2f(q*r*(i-1) + q*Position->x*2, q*r*j + q*Position->y*2);
            glVertex3f((float)(i-1) * (_actualsize/(float)(_size - 1)), _HeightMap[i-1][j], (float)j * (_actualsize/(float)(_size - 1)));
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

float glTerrain::RandRange(float min, float max) {
    return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}

void glTerrain::CalcDirection(float angle)
{
    // cos = z
    // sin = x
    float x = sin(angle * (2*M_PI)/360.f);
    float z = cos(angle * (2*M_PI)/360.f);
    Direction = new vec2f(x, z);

}

void glTerrain::GenTerrain(float speed) {

    // TODO : Calc new Position
    float newx = fmod(Position->x + (_pitch * speed * Direction->x), _size);
    newx = newx < 0 ? newx + _size : newx;

    float newy = fmod(Position->y + (_pitch * speed * Direction->y), _size);
    newy = newy < 0 ? newy + _size : newy;

    Position = new vec2f(
            newx,
            newy
            );

    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {

            float res = noise(i,j, _pitch);
            //res += 0.1 * noise(i,j, _pitch * 10);
            res += 0.04 * noise(i,j, 0.117 + _pitch * 7);
            res /= 1.04;
            res = res * (_max - _min) + _min;
            _HeightMap[i][j] = res < _min ? _min : res;
        }
    }
}

float glTerrain::noise(float i, float j, float pitch)
{
    int prvi = (int)floor(_size + Position->x + (i * _pitch)) % _size;
    int nxti = (int)ceil(_size + Position->x + (i * _pitch)) % _size;
    int prvj = (int)floor(_size + Position->y + (j * _pitch)) % _size;
    int nxtj = (int)ceil(_size + Position->y + (j * _pitch)) % _size;


    double q[4] = {
            _NoiseMap[prvi][prvj],
            _NoiseMap[nxti][prvj],
            _NoiseMap[nxti][nxtj],
            _NoiseMap[prvi][nxtj]
    };

    double blendi= 1 - cos(fmod((_size + Position->x + (i * pitch)), 1.f) * (M_PI/2.f));
    double blendj= 1 - cos(fmod((_size + Position->y + (j * pitch)), 1.f) * (M_PI/2.f));;

    double res = blendi * (q[2] * blendj + q[1] * (1-blendj)) + (1-blendi) * (q[3] * blendj + q[0] * (1-blendj));
    return res;
}

void glTerrain::TerrainColor(float height) {
    int i = 0;
    height -= _min;
    height /= (_max - _min);
    height = fmod(height + 1.0, 1.0);

    for (i = 1; i < _colorCount; i++)
    {
        if (_color_bounds[i] > height) break;
    }
    int pi = i-1;

    float bln = (height - _color_bounds[pi]) / (_color_bounds[i] - _color_bounds[pi]);

    glColor3f((1-bln) * _colors[pi]->x + bln * _colors[i]->x
            , (1-bln) * _colors[pi]->y + bln * _colors[i]->y
            , (1-bln) * _colors[pi]->z + bln * _colors[i]->z);
}
