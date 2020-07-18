//
// Created by thele on 7/18/2020.
//

#include <iostream>
#include "../gameEngine/gameEngine.h"

glModel *M;

void Setup()
{
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightPos[] = {0.0f, 0.0f, 1.0f, 0.0f};
    dbgFunc("setup-vars");

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    dbgFunc("setup-Depth");


    glEnable(GL_FOG);

    glFogi (GL_FOG_MODE, GL_LINEAR);
    glFogfv (GL_FOG_COLOR, new float[4]{0.862, 0.937, 0.933, 0.5});
    glFogf (GL_FOG_DENSITY, 0.2);
    glFogf (GL_FOG_START, 500);
    glFogf (GL_FOG_END, 700);
    glHint (GL_FOG_HINT, GL_NICEST);
    dbgFunc("setup-fog");

    //BLENDING STUFF

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    dbgFunc("setup-mat");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
    dbgFunc("setup-blend");
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    dbgFunc("setup-lights");

    glClearColor(0.862, 0.937, 0.933, 1.0f);

    //glEnable(GL_TEXTURE_2D);

    //// MODEL LOADING ////////////////////////////////////////////////////////////////////////////////////

    M = gameEngine::AddModel("body","../resources/models/body.obj");
    if (M == nullptr) {cout << "Error: Body Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(1, 0.823, 0.239, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-300});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("propeler", "../resources/models/propeler.obj");
    if (M == nullptr) {cout << "Error: Propeler Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.478, 0.478, 0.478, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-300});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("place", TT_MOVE, new float[3]{0, 0, -60});
    M->AddTransformation("elikas", TT_ROTATE, new float[4]{0, 0, 0, 1});
    M->AddMechanic("elikas", new float*[1]{&elikas}, new int[1]{0}, 1);

    M = gameEngine::AddModel("tail", "../resources/models/tailpiece.obj");
    if (M == nullptr) {cout << "Error: Tailpiece Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(1, 0.823, 0.239, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-300});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("wing1", "../resources/models/wing.obj");
    if (M == nullptr) {cout << "Error: Wing 1 Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.901, 0.6, 0.098, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-300});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("wing2", "../resources/models/wing.obj");
    if (M == nullptr) {cout << "Error: Wing 2 Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.901, 0.6, 0.098, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-300});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("flip", TT_ROTATE, new float[4]{180,0,0,1});

    M = gameEngine::AddModel("flap1", "../resources/models/flap.obj");
    if (M == nullptr) {cout << "Error: Flap 1 Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.780, 0.458, 0, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-300});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("flap2", "../resources/models/flap.obj");
    if (M == nullptr) {cout << "Error: Flap 2 Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.780, 0.458, 0, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-300});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("flip", TT_ROTATE, new float[4]{180,0,0,1});
}
