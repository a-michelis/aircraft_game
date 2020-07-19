//
// Created by thele on 7/17/2020.
//

using namespace std;

#include <list>
#include <iostream>
#include "gameEngine.h"

// #########################################################################################################
// HIDDEN VARIABLES ########################################################################################
// #########################################################################################################

bool            _displaySet         = false;            // True when we set display callback function.
                                                        // ONLY THEN we start the engine.

bool            _setupSet           = false;            // True when we set Setup function
void            (*_setupFunc)(void) = nullptr;          // Contains the Setup Function

bool            _closeSet           = false;            // True when we set Close function
void            (*_closeFunc)(void) = nullptr;          // Contains the Closing Function

list<texture*> *_textures;
list<glModel*> *_models;

// #########################################################################################################
// METHOD DEFINITIONS ######################################################################################
// #########################################################################################################

void gameEngine::Init(
        vec2 *WindowPosition,
        vec2 *WindowDimensions,
        const char *WindowTitle,
        GLuint *glOptions,
        int glOptionsCount,
        int *argc, char **argv
        )
{
    // We OR all GL options together, and we store them in "opts" variable
    unsigned int opts = 0;
    for (int i = 0; i < glOptionsCount; i++) {opts |= glOptions[i];}

    // Its time for actual code: We init our GL library, and we pass opts as Display mode options.
    glutInit(argc, argv);
    glutInitDisplayMode(opts);

    // Next thing is specifying the dimensions and possition of the window.
    glutInitWindowSize(WindowDimensions->x, WindowDimensions->y);
    glutInitWindowPosition(WindowPosition->x, WindowPosition->y);

    // Last, we create the desired window, while we define its title according our arguements.
    glutCreateWindow(WindowTitle);

    _textures = new list<texture*>;
    _models = new list<glModel*>;

    // What's left is defining the functions, and some other things (setup etc) in order to
    // start the glutMainLoop() function.
}

void gameEngine::DisplayCallback(void (*function)(void)) {
    if (function == nullptr) return;
    glutDisplayFunc(function);
    _displaySet = true;
}

void gameEngine::ResizeCallback(void (*function)(int, int)) {
    if (function == nullptr) return;
    glutReshapeFunc(function);
}

void gameEngine::IdleCallback(void (*function)(void)) {
    if (function == nullptr) return;
    glutIdleFunc(function);
}

void gameEngine::SetupCallback(void (*function)(void)) {
    if (function == nullptr) return;
    _setupSet = true;
    _setupFunc = function;
}

void gameEngine::CloseCallback(void (*function)(void)) {
    if (function == nullptr) return;
    _closeSet = true;
    _closeFunc = function;
}

void gameEngine::KeyDownCallback(void (*function)(unsigned char, int, int), bool KeyRepeat) {
    if (function == nullptr) return;
    glutKeyboardFunc(function);
    glutIgnoreKeyRepeat(!KeyRepeat);
}

void gameEngine::KeyUpCallback(void (*function)(unsigned char, int, int)) {
    if (function == nullptr) return;
    glutKeyboardUpFunc(function);
}

void gameEngine::AddTexture(const char *filename, const char *Id, int type){
    if (_textures->size() > 0)
    {
        for (auto it = _textures->begin(); it != _textures->end(); it = next(it))
            if ((*it)->id->compare(Id) == 0) return;
    }

    GLuint tex;
    BMPClass loader;
    char err = BMPLoad(filename, loader);
    cout << "Loading Texture: " << TranslateBMPError(err) << "\n";
    if (err > 0) exit(-1);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            loader.width,
            loader.height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            loader.bytes
    );

    glBindTexture(GL_TEXTURE_2D, 0);

    _textures->push_back(new texture(tex, Id));
}

void gameEngine::SetTexture(const char *Id) {
    if (_textures->size() == 0) return;

    for (auto it = _textures->begin(); it != _textures->end(); it = next(it))
    {
        if ((*it)->id->compare(Id) == 0)
        {
            glEnable(GL_TEXTURE_2D);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, (*it)->texId);
            return;
        }
    }
}

void gameEngine::UnsetTexture() {
    glDisable(GL_TEXTURE_2D);
}

void gameEngine::RemoveTexture(const char *Id) {
    if (_textures->size() == 0) return;

    for (auto it = _textures->begin(); it != _textures->end(); it = next(it))
    {
        if ((*it)->id->compare(Id) == 0)
        {
            glDeleteTextures(1, &((*it)->texId));
            _textures->remove((*it));
            return;
        }
    }
}

void gameEngine::RemoveAllTextures() {
    while (_textures->size() > 0)
    {
        glDeleteTextures(1, &((*_textures->begin())->texId));
        _textures->remove((*_textures->begin()));
    }
}

 glModel *gameEngine::AddModel(const char *Id, const char *filename) {
     {
         if(_models->size() > 0)
         {
             for (auto it = _models->begin(); it != _models->end(); it = next(it))
             {
                 if ((*it)->ModelName->compare(Id) == 0) return (*it);
             }

         }

         _models->push_back(new glModel(Id, filename));
         return _models->back();
     }
}

glModel *gameEngine::GetModel(const char *Id)
{
    if (_models->size() == 0) return nullptr;

    for (auto it = _models->begin(); it != _models->end(); it = next(it))
    {
        if ((*it)->ModelName->compare(Id) == 0) return (*it);
    }
    return nullptr;
}

glModel *gameEngine::AddModel(const char *Id, vector<vec3f *> *vertices, vector<vec3f *> *normals,
                              vector<triangle *> *triangles) {
    if(_models->size() > 0)
    {
        for (auto it = _models->begin(); it != _models->end(); it = next(it))
        {
            if ((*it)->ModelName->compare(Id) == 0) return (*it);
        }
    }

    _models->push_back(new glModel(Id, vertices, normals, triangles));
    return _models->back();
}

void gameEngine::RemoveModel(const char *Id) {
    if(_models->size() > 0)
    {
        for (auto it = _models->begin(); it != _models->end(); it = next(it))
        {
            if ((*it)->ModelName->compare(Id) == 0)
            {
                _models->remove((*it));
                return;
            }
        }
    }
}

void gameEngine::RemoveAllModels() {
    while (_models->size() > 0)
    {
        _models->remove((*_models->begin()));
    }
}

void gameEngine::DrawModels() {
    if (_models->size() == 0) return;
    for(auto it = _models->begin(); it != _models->end(); it = next(it))
    {
        (*it)->DrawModel();
    }
}

void gameEngine::StartLoop() {
    // We check if Display function is set.
    if (!(_displaySet)) {return;}

    // If all ok, we check if there's a setup function. If it does, we run it.
    if (_setupSet) { _setupFunc(); }

    // We start the loop.
    glutMainLoop();

    // We check if there's a close function. If it does, we run it.
    if (_closeSet) { _closeFunc(); }

}


