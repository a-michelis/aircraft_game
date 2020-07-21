//
// Created by thele on 7/17/2020.
//
#pragma once

#ifndef AIRCRAFT_GAME_STRUCTS_H
#define AIRCRAFT_GAME_STRUCTS_H

using namespace std;

#include <string>
#include "gameEngine/gameEngine.h"

typedef struct _vec2
{
    int x; int y;
    _vec2(int X, int Y){x=X;y=Y;}
    _vec2(_vec2 *orig){x=orig->x; y=orig->y;}
} vec2;

typedef struct _vec2f
{
    float x; float y;
    _vec2f(float X, float Y){x=X;y=Y;}
    _vec2f(_vec2f *orig){x=orig->x; y=orig->y;}
} vec2f;

typedef struct _vec3f
{
    float x; float y; float z;
    _vec3f(float X, float Y, float Z){x=X;y=Y;z=Z;}
    _vec3f(_vec3f *orig){x=orig->x; y=orig->y;z=orig->z;}
} vec3f;

typedef struct _vec4f
{
    float x; float y; float z; float w;
    _vec4f(float X, float Y, float Z, float W){x=X;y=Y;z=Z;w=W;}
    _vec4f(_vec4f *orig){x=orig->x; y=orig->y;z=orig->z;w=orig->w;}
} vec4f;

typedef struct _color
{
    float r; float g; float b; float a;
    _color(float R, float G, float B, float A){r=R;g=G;b=B;a=A;}
    _color(float R, float G, float B){r=R;g=G;b=B;a=1.f;}
    _color(_color *orig){r=orig->r; g=orig->g; b=orig->b; a=orig->a;}
    _color(vec4f *orig){r=orig->x; g=orig->y; b=orig->z; a=orig->w;}
    _color(vec3f *orig){r=orig->x; g=orig->y; b=orig->z; a=1.f;}
} color;

typedef struct _triangle
{
    int vertices[3];
    int normals[3];
    _triangle(int v1, int v2, int v3, int n1, int n2, int n3){
        vertices[0] = v1; vertices[1] = v2; vertices[2] = v3;
        normals[0] = n1; normals[1] = n2; normals[2] = n3;
    }
    _triangle(int v[3], int n[3]){
        for (int i = 0; i < 3; i++)
        {
            vertices[i] = v[i];
            normals[i] = n[i];
        }
    }
    _triangle(_triangle *orig){
        for (int i = 0; i < 3; i++)
        {
            vertices[i] = orig->vertices[i];
            normals[i] = orig->normals[i];
        }
    }
} triangle;

typedef enum {TT_MOVE, TT_ROTATE, TT_SCALE} TransformationType;

typedef struct _transformation
{
    std::string *id;
    TransformationType type;
    float *args;
    _transformation(const char *Id, TransformationType Type, float Args[]){
        id = new std::string(Id);
        type = Type;
        switch (type) {
            case TT_MOVE:
                args = new float[3];
                for (int i = 0; i < 3; i++) args[i] = Args[i];
                break;
            case TT_SCALE:
                args = new float[3];
                for (int i = 0; i < 3; i++) args[i] = Args[i];
                break;
            case TT_ROTATE:
                args = new float[4];
                for (int i = 0; i < 4; i++) args[i] = Args[i];
                break;
            default:
                args = new float[4];
                for (int i = 0; i < 4; i++) args[i] = 0.f;
                break;
        }
    }
    _transformation(_transformation *orig){
        id = new std::string(orig->id->c_str());
        type = orig->type;
        switch (type) {
            case TT_MOVE:
                args = new float[3];
                for (int i = 0; i < 3; i++) args[i] = orig->args[i];
                break;
            case TT_SCALE:
                args = new float[3];
                for (int i = 0; i < 3; i++) args[i] = orig->args[i];
                break;
            case TT_ROTATE:
                args = new float[4];
                for (int i = 0; i < 4; i++) args[i] = orig->args[i];
                break;
            default:
                args = new float[4];
                for (int i = 0; i < 4; i++) args[i] = 0.f;
                break;
        }
    }
} transformation;

typedef struct _mechanic
{
    transformation *transf;
    float **dependencies;
    int *argIndex;
    int indexes;

    _mechanic(transformation **Transf, float **Dependencies, int *ArgIndex, int argIndexCount){
        transf = *Transf;
        dependencies = new float*[argIndexCount];
        indexes = argIndexCount;
        argIndex = new int[argIndexCount];
        for (int i = 0; i < argIndexCount; i++) {argIndex[i] = ArgIndex[i]; dependencies[i] = Dependencies[i]; }
    }
} mechanic;

typedef struct _texture
{
    GLuint texId;
    string *id;

    _texture(GLuint TexId, const char *Id){
        texId = TexId;
        id = new string(Id);
    }
} texture;
#endif //AIRCRAFT_GAME_STRUCTS_H
