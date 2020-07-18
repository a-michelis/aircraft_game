//
// Created by thele on 7/17/2020.
//
#pragma once

#ifndef AIRCRAFT_GAME_GAMEENGINE_H
#define AIRCRAFT_GAME_GAMEENGINE_H

using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include "../structs.h"
#include "../glModel/glModel.h"
#include "../BMPLoader/BMPLoader.h"
#include "../callbacks/callbacks.h"


class gameEngine {
public:
    // Setup and Initalization of GL library
    static void Init(
            vec2 *WindowPosition,
            vec2 *WindowDimensions,
            const char *WindowTitle,
            GLuint glOptions[], int glOptionsCount,
            int *argc, char *argv[]
            );

    // GL CallBack Functions Setup
    static void DisplayCallback(void (*function)(void));
    static void ResizeCallback(void (*function)(int, int));
    static void IdleCallback(void (*function)(void));
    static void SetupCallback(void (*function)(void));
    static void CloseCallback(void (*function)(void));
    // TODO: Keyboard callback and mouse callback

    // Texture Handling Functions
    static void AddTexture(const char *filename, const char *Id, int type);
    static void SetTexture(const char *Id);
    static void UnsetTexture();
    static void RemoveTexture(const char *Id);
    static void RemoveAllTextures();

    // Model Handling Functions
    static glModel *GetModel(const char *Id);
    static glModel *AddModel(const char *Id, const char *filename);
    static glModel *AddModel(const char *Id, vector<vec3f*> *vertices, vector<vec3f*> *normals, vector<triangle*> *triangles);
    static void RemoveModel(const char *Id);
    static void RemoveAllModels();
    static void DrawModels();

    // Loop Start
    static void StartLoop();
};

void dbgFunc(const char *place);

#endif //AIRCRAFT_GAME_GAMEENGINE_H
