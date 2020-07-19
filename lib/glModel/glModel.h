//
// Created by thele on 7/17/2020.
//
#pragma once

#ifndef AIRCRAFT_GAME_GLMODEL_H
#define AIRCRAFT_GAME_GLMODEL_H

using namespace std;

#include <vector>
#include <list>

#include "../gameEngine/gameEngine.h"

class glModel {
    vector<vec3f*> *_vertices;
    vector<vec3f*> *_normals;
    vector<triangle*> *_triangles;
    list<transformation*> *_transformations;
    list<mechanic*> *_mechanics;
    bool _HasKa = false;
    bool _HasKd = false;
    bool _HasKs = false;
    bool _HasIl = false;
    bool _HasNs = false;
    vec3f *_Ka = nullptr;
    vec3f *_Kd = nullptr;
    vec3f *_Ks = nullptr;
    float _il = 0.f;
    float _ns = 0.f;


public:
    string *ModelName;
    color *ModelColor = new color(1,1,1,1);

    glModel(const char* modelName, const char* filename);
    glModel(const char* modelName,vector<vec3f*> *vertices, vector<vec3f*> *normals, vector<triangle*> *triangles);

    void AddTransformation(const char* Id, TransformationType type, float args[]);
    void AlterTransformation (const char* Id, TransformationType Type, float Args[]);
    transformation *GetTransformation(const char* Id);
    void RemoveTransformation(const char* Id);
    void RemoveTransformations();

    void DrawModel();

    void AddMechanic(const char* Id, float **Dependencies, int indexes[], int indexCount);
    void AlterMechanic(const char* Id, float **Dependencies, int indexes[], int indexCount);
    void RemoveMechanic(const char* Id, bool RemoveTransformationAsWell = false);
    void RemoveMechanics(bool RemoveTransformationsAsWell = false);

private:
    void LoadFromFile(const char *filename);
    void LoadMaterials(const char *filename);
    void ApplyTransformations();
    void UpdateMechanics();
};


#endif //AIRCRAFT_GAME_GLMODEL_H
