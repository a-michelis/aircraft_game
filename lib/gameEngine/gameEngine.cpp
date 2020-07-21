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

bool            displaySet         = false;            // True when we set display callback function.
                                                       // ONLY THEN we start the engine.

bool            setupSet           = false;            // True when we set Setup function
void            (*setupFunc)()     = nullptr;          // Contains the Setup Function

bool            closeSet           = false;            // True when we set Close function
void            (*closeFunc)()     = nullptr;          // Contains the Closing Function

list<texture*> *Textures;
list<glModel*> *Models;

// #########################################################################################################
// METHOD DEFINITIONS ######################################################################################
// #########################################################################################################

void gameEngine::Init(
        vec2 *WindowPosition,
        vec2 *WindowDimensions,
        const char *WindowTitle,
        const GLuint *glOptions,
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

    Textures = new list<texture*>;
    Models = new list<glModel*>;

    // What's left is defining the functions, and some other things (setup etc) in order to
    // start the glutMainLoop() function.
}

void gameEngine::DisplayCallback(void (*function)()) {
    if (function == nullptr) return;
    glutDisplayFunc(function);
    displaySet = true;
}

void gameEngine::ResizeCallback(void (*function)(int, int)) {
    if (function == nullptr) return;
    glutReshapeFunc(function);
}

void gameEngine::IdleCallback(void (*function)()) {
    if (function == nullptr) return;
    glutIdleFunc(function);
}

void gameEngine::SetupCallback(void (*function)()) {
    if (function == nullptr) return;
    setupSet = true;
    setupFunc = function;
}

void gameEngine::CloseCallback(void (*function)()) {
    if (function == nullptr) return;
    closeSet = true;
    closeFunc = function;
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
    if (!Textures->empty())
    {
        _List_iterator<texture *> it;
        for (it = Textures->begin(); it != Textures->end(); it = next(it))
            if (*(*it)->id == Id) return;
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

    Textures->push_back(new texture(tex, Id));
}

GLuint gameEngine::GetTexture(const char *Id) {
    if (Textures->empty()) return 0;

    for (auto it = Textures->begin(); it != Textures->end(); it = next(it))
    {
        if (*(*it)->id == Id)
        {
            return (*it)->texId;
        }
    }
    return 0;
}

//void gameEngine::RemoveTexture(const char *Id) {
//    if (Textures->empty()) return;
//
//    _List_iterator<texture *> it;
//    for (it = Textures->begin(); it != Textures->end(); it = next(it))
//    {
//        if (*(*it)->id == Id)
//        {
//            glDeleteTextures(1, &((*it)->texId));
//            Textures->remove((*it));
//            return;
//        }
//    }
//}

void gameEngine::RemoveAllTextures() {
    while (!Textures->empty())
    {
        glDeleteTextures(1, &((*Textures->begin())->texId));
        Textures->remove((*Textures->begin()));
    }
}

 glModel *gameEngine::AddModel(const char *Id, const char *filename) {
     {
         if(!Models->empty())
         {
             for (auto it = Models->begin(); it != Models->end(); it = next(it))
             {
                 if (*(*it)->ModelName == Id) return (*it);
             }

         }

         Models->push_back(new glModel(Id, filename));
         return Models->back();
     }
}

//glModel *gameEngine::GetModel(const char *Id)
//{
//    if (Models->empty()) return nullptr;
//
//    _List_iterator<glModel *> it;
//    for (it = Models->begin(); it != Models->end(); it = next(it))
//    {
//        if (*(*it)->ModelName == Id) return (*it);
//    }
//    return nullptr;
//}

//void gameEngine::RemoveModel(const char *Id) {
//    if(!Models->empty())
//    {
//        _List_iterator<glModel *> it;
//        for (it = Models->begin(); it != Models->end(); it = next(it))
//        {
//            if (*(*it)->ModelName == Id)
//            {
//                Models->remove((*it));
//                return;
//            }
//        }
//    }
//}

void gameEngine::RemoveAllModels() {
    while (!Models->empty())
    {
        Models->remove((*Models->begin()));
    }
}

void gameEngine::DrawModels() {
    if (Models->empty()) return;
    for(auto it = Models->begin(); it != Models->end(); it = next(it))
    {
        (*it)->DrawModel();
    }
}

void gameEngine::StartLoop() {
    // We check if Display function is set.
    if (!(displaySet)) {return;}

    // If all ok, we check if there's a setup function. If it does, we run it.
    if (setupSet) { setupFunc(); }

    // We start the loop.
    glutMainLoop();

    // We check if there's a close function. If it does, we run it.
    if (closeSet) { closeFunc(); }

}


