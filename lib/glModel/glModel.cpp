//
// Created by thele on 7/17/2020.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "../gameEngine/gameEngine.h"
#include "glModel.h"


// ############################################################################################
// Constructors ###############################################################################
// ############################################################################################

glModel::glModel(const char* modelName, const char *filename) {
    ModelName = new string(modelName);
    _vertices = new vector<vec3f*>();
    _normals = new vector<vec3f*>();
    _triangles = new vector<triangle*>();
    LoadFromFile(filename);

    string *mf = new string(filename);
    mf->replace(mf->find(".obj"),4,".mtl");
    LoadMaterials(mf->c_str());

    _transformations = new list<transformation*>();
    _mechanics = new list<mechanic*>();
}

glModel::glModel(const char* modelName, vector<vec3f *> *vertices, vector<vec3f *> *normals, vector<triangle *> *triangles) {
    ModelName = new string(modelName);

    if (vertices->size() > 0)
        _vertices = new vector<vec3f*>(vertices->begin(), vertices->end());

    if (normals->size() > 0)
        _normals = new vector<vec3f*>(normals->begin(), normals->end());

    if (triangles->size() > 0)
        _triangles = new vector<triangle*>(triangles->begin(), triangles->end());

    _transformations = new list<transformation*>();
    _mechanics = new list<mechanic*>();
}

// ############################################################################################
// Transformations ############################################################################
// ############################################################################################

void glModel::AddTransformation(const char *Id, TransformationType type, float *args) {
    if(_transformations->size() > 0)
    {
        for(auto it = _transformations->begin(); it != _transformations->end(); it = next(it))
        {
            if ((*it)->id->compare(Id) == 0) return;
        }
    }

    _transformations->push_back(new transformation(Id, type, args));


    //cout << "Transf Added '" << Id << "'\n";
}

void glModel::AlterTransformation(const char *Id, TransformationType Type, float *Args) {
    if (_transformations->size() == 0) return;

    for (auto it = _transformations->begin(); it != _transformations->end(); it = next(it)) {
        if ((*it)->id->compare(Id) == 0)
        {
            (*it) = new transformation(Id, Type, Args);
            //cout << "Transf Altered '" << Id << "'\n";
            return;
        }
    }

    //cout << "Transf NotFound'" << Id << "'\n";
}

transformation *glModel::GetTransformation(const char *Id) {
    if (_transformations->size() == 0) return nullptr;

    for (auto it = _transformations->begin(); it != _transformations->end(); it = next(it)) {
        if ((*it)->id->compare(Id) == 0) {
            //cout << "Transf Found'" << *(*it)->id << "'\n";
            return (*it);
        }
    }

    return nullptr;
}

void glModel::RemoveTransformation(const char *Id) {
    if (_transformations->size() == 0) return;

    for (auto it = _transformations->begin(); it != _transformations->end(); it = next(it)) {
        if ((*it)->id->compare(Id) == 0)
        {
            _transformations->remove((*it));
            return;
        }
    }
}

void glModel::RemoveTransformations() {
    if (_transformations->size() == 0) return;

    while (_transformations->size() > 0)
    {
        _transformations->remove(*(_transformations->begin()));
    }
}

// ############################################################################################
// Mechanics ##################################################################################
// ############################################################################################

void glModel::AddMechanic(const char *Id, float **Dependencies, int *indexes, int indexCount) {

    if (_transformations->size() == 0) return;
    transformation **t = nullptr;

    for(auto it = _transformations->begin(); it != _transformations->end(); it = next(it))
    {
        if ((*it)->id->compare(Id) == 0) {t = &(*it); break;}
    }

    if (t == nullptr) return;

    if(_mechanics->size() > 0)
    {
        for(auto it = _mechanics->begin(); it != _mechanics->end(); it = next(it))
        {
            if ((*it)->transf->id->compare(Id) == 0) return;
        }
    }

    _mechanics->push_back(new mechanic (t, Dependencies, indexes, indexCount));
}

void glModel::AlterMechanic(const char *Id, float **Dependencies, int *indexes, int indexCount) {
    if (_mechanics->size() == 0) return;

    transformation **t = nullptr;

    for(auto it = _transformations->begin(); it != _transformations->end(); it = next(it))
    {
        if ((*it)->id->compare(Id) == 0) {t = &(*it); break;}
    }

    if (t == nullptr) return;

    for(auto it = _mechanics->begin(); it != _mechanics->end(); it = next(it))
    {
        if ((*it)->transf->id->compare(Id) == 0)
        {
            (*it) = new mechanic (t, Dependencies, indexes, indexCount);
            return;
        }
    }
}

void glModel::RemoveMechanic(const char *Id, bool RemoveTransformationAsWell) {
    if (_mechanics->size() == 0) return;
    for(auto it = _mechanics->begin(); it != _mechanics->end(); it = next(it))
    {
        if ((*it)->transf->id->compare(Id) == 0)
        {
            if (RemoveTransformationAsWell)
                RemoveTransformation((*it)->transf->id->c_str());

            _mechanics->remove((*it));

            return;
        }
    }
}

void glModel::RemoveMechanics(bool RemoveTransformationsAsWell) {
    while (_mechanics->size() > 0)
    {
        if (RemoveTransformationsAsWell)
            RemoveTransformation((*(_mechanics->begin()))->transf->id->c_str());

        _mechanics->remove(*(_mechanics->begin()));
    }
}

// ############################################################################################
// Drawing ####################################################################################
// ############################################################################################

void glModel::DrawModel() {

    glPushMatrix();

        //glEnable(GL_COLOR_MATERIAL);
        if (_HasKa)             { glMaterialfv(GL_FRONT, GL_AMBIENT, new float[3]{_Ka->x, _Ka->y, _Ka->z}); }
        if (_HasKd)             { glMaterialfv(GL_FRONT, GL_DIFFUSE, new float[3]{_Kd->x, _Kd->y, _Kd->z}); }
        if (_HasKs && !_HasIl)  { glMaterialfv(GL_FRONT, GL_SPECULAR, new float[3]{_Ks->x, _Ks->y, _Ks->z}); }
        if (_HasIl)             {  if (_il == 2) glMaterialfv(GL_FRONT, GL_SPECULAR, new float[3]{_Ks->x, _Ks->y, _Ks->z}); }
        if (_HasNs)             { glMaterialf(GL_FRONT, GL_SHININESS, _ns); }

        UpdateMechanics();
        ApplyTransformations();

        glBegin(GL_TRIANGLES);
            glColor4f(ModelColor->r, ModelColor->g, ModelColor->b, ModelColor->a);
            for(auto it = _triangles->begin(); it != _triangles->end(); it = next(it))
            {
                triangle *f = *it;

                vec3f *v[3] =
                        {
                            _vertices->at(f->vertices[0]),
                            _vertices->at(f->vertices[1]),
                            _vertices->at(f->vertices[2])
                        };

                vec3f *n[3] =
                        {
                            _normals->at(f->normals[0]),
                            _normals->at(f->normals[1]),
                            _normals->at(f->normals[2])
                        };

                glNormal3f(n[0]->x, n[0]->y, n[0]->z);
                glVertex3f(v[0]->x, v[0]->y, v[0]->z);

                glNormal3f(n[1]->x, n[1]->y, n[1]->z);
                glVertex3f(v[1]->x, v[1]->y, v[1]->z);

                glNormal3f(n[2]->x, n[2]->y, n[2]->z);
                glVertex3f(v[2]->x, v[2]->y, v[2]->z);
//                cout << "################## " << c++ << "################## " << endl;
//                cout << "["<< v[0]->x <<", " << v[0]->y << ", " << v[0]->z << "]" << endl;
//                cout << "["<< v[1]->x <<", " << v[1]->y << ", " << v[1]->z << "]" << endl;
//                cout << "["<< v[2]->x <<", " << v[2]->y << ", " << v[2]->z << "]" << endl << endl;
            }
        glEnd();

        //glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

// ############################################################################################
// File Load ##################################################################################
// ############################################################################################

void glModel::LoadFromFile(const char *filename) {
    ifstream obj_file(filename);

    string line;
    while (getline(obj_file, line))
    {

        istringstream iss(line);

        string code = line.substr(0, line.find(' '));

        if (code == "v")
        {
            std::string cd;
            float x, y, z;
            if (!(iss >> cd >> x >> y >> z)) { break; } // error

            _vertices->push_back(new vec3f(x, y, z));

        }

        else if (code == "vn")
        {
            std::string cd;
            float x, y, z;
            if (!(iss >> cd >> x >> y >> z)) { break; } // error

            _normals->push_back(new vec3f(x, y, z));

        }

        else if (code == "f")
        {
            string cd, f1, f2, f3;
            if (!(iss >> cd >> f1 >> f2 >> f3)) { break; } // error

            int f1v = stoi(f1.substr(0, f1.find("//")), nullptr, 10);
            int f1n = stoi(f1.substr(f1.find("//") + 2), nullptr, 10);

            int f2v = stoi(f2.substr(0, f2.find("//")), nullptr, 10);
            int f2n = stoi(f2.substr(f2.find("//") + 2), nullptr, 10);

            int f3v = stoi(f3.substr(0, f3.find("//")), nullptr, 10);
            int f3n = stoi(f3.substr(f3.find("//") + 2), nullptr, 10);

            _triangles->push_back(new triangle(new int[3]{f1v-1, f2v-1, f3v-1}, new int[3]{f1n-1, f2n-1, f3n-1}));
        }
        else continue;

    }

    obj_file.close();
}



void glModel::LoadMaterials(const char *filename) {
    ifstream obj_file(filename);

    string line;
    while (getline(obj_file, line))
    {
        istringstream iss(line);

        if (line.compare(0,1,"#") == 0) continue;

        while(line.c_str()[0] == ' ' || line.c_str()[0] == '\t') line.erase(0,1);

        string code = line.substr(0, line.find(' '));

        if (!_HasKa && code == "Ka")
        {
            std::string cd;
            float x, y, z;
            if (!(iss >> cd >> x >> y >> z)) { break; } // error

            _Ka = new vec3f(x*0.3, y*0.3, z*0.3);
            _HasKa = true;
        }

        else if (!_HasKd && code == "Kd")
        {
            std::string cd;
            float x, y, z;
            if (!(iss >> cd >> x >> y >> z)) { break; } // error

            _Kd = new vec3f(x*0.3, y*0.3, z*0.3);
            _HasKd = true;
        }

        else if (!_HasKs && code == "Ks")
        {
            std::string cd;
            float x, y, z;
            if (!(iss >> cd >> x >> y >> z)) { break; } // error

            _Ks = new vec3f(x*0.3, y*0.3, z*0.3);
            _HasKs = true;
        }

        else if (!_HasIl && code == "illum")
        {
            std::string cd;
            float x;
            if (!(iss >> cd >> x)) { break; } // error

            _il = x*0.3;
            _HasIl = true;
        }

        else if (!_HasNs && code == "Ns")
        {
            std::string cd;
            float x;
            if (!(iss >> cd >> x)) { break; } // error

            _ns = x*0.3;
            _HasNs = true;
        }
        else continue;

    }

    obj_file.close();
}

// ############################################################################################
// Transformations application ################################################################
// ############################################################################################

void glModel::ApplyTransformations() {
    if (_transformations->size() == 0) return;

//    int c = 0;

    for (auto it = _transformations->begin(); it != _transformations->end(); it = next(it))
    {
        transformation *t = (*it);

        switch(t->type){
            case TT_MOVE:
//                cout << ModelName->c_str() << ": Move[" << c++ << "] = " << t->id->c_str() << endl;
                glTranslatef(t->args[0], t->args[1], t->args[2]);
                break;
            case TT_SCALE:
//                cout << ModelName->c_str() << ": Scale[" << c++ << "] = " << t->id->c_str() << endl;
                glScalef(t->args[0], t->args[1], t->args[2]);
                break;
            case TT_ROTATE:
//                cout << ModelName->c_str() << ": Rotate[" << c++ << "] = " << t->id->c_str() << endl;
                glRotatef(t->args[0], t->args[1], t->args[2], t->args[3]);
                break;
            default:
                break;
        }
//        string *st = new string();
//        st->append(ModelName->c_str()); st->append("-"); st-> append(t->id->c_str());
    }
}

// ############################################################################################
// Mechanics application ######################################################################
// ############################################################################################

void glModel::UpdateMechanics() {
    if (_mechanics->size() == 0) return;

    for (auto it = _mechanics->begin(); it != _mechanics->end(); it = next(it))
    {
        for(int i = 0; i < (*it)->indexes; i++)
        {
            (*it)->transf->args[(*it)->argIndex[i]] = *((*it)->dependencies[i]);
        }
    }
}
