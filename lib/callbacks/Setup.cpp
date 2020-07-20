//
// Created by thele on 7/18/2020.
//

#include <iostream>
#include "../gameEngine/gameEngine.h"


GLfloat lightPos[] = {10.0f, 50.0f, -90.f, 0.0f};

glTerrain *TERA = new glTerrain(250, 1600, -1, 100, 0.08,
    new float[8] {0, 0.05, 0.06, 0.3, 0.4, 0.7, 0.8, 1},
    new vec3f*[8]{
        new vec3f(0.094118, 0.188235, 0.388235),
        new vec3f(0.298039, 0.380392, 0.560784),
        new vec3f(0.254902, 0.580392, 0.278431),
        new vec3f(0.372549, 0.529412, 0.384314),
        new vec3f(0.701961, 0.709804, 0.611765),
        new vec3f(0.870588, 0.878431, 0.756863),
        new vec3f(0.941176, 0.941176, 0.941176),
        new vec3f(1,1,1)
    },
    8
);

void Setup()
{
    GLfloat ambientLight[] = {0.01f, 0.01f, 0.01f, 0.4f};
    GLfloat diffuseLight[] = {0.6f, 0.6f, 0.6f, 0.4f};

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glEnable(GL_FOG);

    glFogi (GL_FOG_MODE, GL_LINEAR);
    glFogfv (GL_FOG_COLOR, new float[4]{0.862, 0.937, 0.933, 0.3});
    glFogf (GL_FOG_DENSITY, 0.2);
    glFogf (GL_FOG_START, 400);
    glFogf (GL_FOG_END, 600);
    glHint (GL_FOG_HINT, GL_NICEST);

    //BLENDING STUFF

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glClearColor(0.862, 0.937, 0.933, 1.0f);

    //// TEXTURE LOADING //////////////////////////////////////////////////////////////////////////////////

    glEnable(GL_TEXTURE_2D);
    gameEngine::AddTexture("../resources/textures/flora.bmp", "low", GL_LINEAR);
    gameEngine::AddTexture("../resources/textures/mixed.bmp", "mid", GL_LINEAR);
    gameEngine::AddTexture("../resources/textures/dirt.bmp", "high", GL_LINEAR);

    //// MODEL LOADING ////////////////////////////////////////////////////////////////////////////////////

    glModel *M = gameEngine::AddModel("body","../resources/models/body.obj");
    if (M == nullptr) {cout << "Error: Body Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(1, 0.823, 0.239, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-90});
    M->AddTransformation("scale", TT_SCALE, new float[3]{0.3,0.3,0.3});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("zrotation", TT_ROTATE, new float[4]{0,0,0,1});
    M->AddMechanic("zrotation", new float*[1]{(&zrot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("propeler", "../resources/models/propeler.obj");
    if (M == nullptr) {cout << "Error: Propeler Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.478, 0.478, 0.478, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-90});
    M->AddTransformation("scale", TT_SCALE, new float[3]{0.3,0.3,0.3});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("place", TT_MOVE, new float[3]{0, 0, -60});
    M->AddTransformation("elikas", TT_ROTATE, new float[4]{0, 0, 0, 1});
    M->AddMechanic("elikas", new float*[1]{&elikas}, new int[1]{0}, 1);
    M->AddTransformation("zrotation", TT_ROTATE, new float[4]{0,0,0,1});
    M->AddMechanic("zrotation", new float*[1]{(&zrot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("tail", "../resources/models/tailpiece.obj");
    if (M == nullptr) {cout << "Error: Tailpiece Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(1, 0.823, 0.239, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-90});
    M->AddTransformation("scale", TT_SCALE, new float[3]{0.3,0.3,0.3});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("zrotation", TT_ROTATE, new float[4]{0,0,0,1});
    M->AddMechanic("zrotation", new float*[1]{(&zrot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("wing1", "../resources/models/wing.obj");
    if (M == nullptr) {cout << "Error: Wing 1 Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.901, 0.6, 0.098, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-90});
    M->AddTransformation("scale", TT_SCALE, new float[3]{0.3,0.3,0.3});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("zrotation", TT_ROTATE, new float[4]{0,0,0,1});
    M->AddMechanic("zrotation", new float*[1]{(&zrot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("wing2", "../resources/models/wing.obj");
    if (M == nullptr) {cout << "Error: Wing 2 Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.901, 0.6, 0.098, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-90});
    M->AddTransformation("scale", TT_SCALE, new float[3]{0.3,0.3,0.3});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("flip", TT_ROTATE, new float[4]{180,0,0,1});
    M->AddTransformation("zrotation", TT_ROTATE, new float[4]{0,0,0,1});
    M->AddMechanic("zrotation", new float*[1]{(&zrot)}, new int[1]{0}, 1);

    M = gameEngine::AddModel("flap1", "../resources/models/flap.obj");
    if (M == nullptr) {cout << "Error: Flap 1 Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.780, 0.458, 0, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-90});
    M->AddTransformation("scale", TT_SCALE, new float[3]{0.3,0.3,0.3});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("zrotation", TT_ROTATE, new float[4]{0,0,0,1});
    M->AddMechanic("zrotation", new float*[1]{(&zrot)}, new int[1]{0}, 1);
    M->AddTransformation("mech_rot", TT_ROTATE, new float[4]{0,1,0,0});
    M->AddMechanic("mech_rot", new float*[1]{(&w1r)}, new int[1]{0}, 1);
    M->AddTransformation("mech_move", TT_MOVE, new float[3]{0,0,0});
    M->AddMechanic("mech_move", new float*[2]{(&w1m), (&w1b)}, new int[2]{1,2}, 2);

    M = gameEngine::AddModel("flap2", "../resources/models/flap.obj");
    if (M == nullptr) {cout << "Error: Flap 2 Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.780, 0.458, 0, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-90});
    M->AddTransformation("scale", TT_SCALE, new float[3]{0.3,0.3,0.3});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("flip", TT_ROTATE, new float[4]{180,0,0,1});
    M->AddTransformation("zrotation", TT_ROTATE, new float[4]{0,0,0,1});
    M->AddMechanic("zrotation", new float*[1]{(&zrot)}, new int[1]{0}, 1);
    M->AddTransformation("mech_rot", TT_ROTATE, new float[4]{0,1,0,0});
    M->AddMechanic("mech_rot", new float*[1]{(&w2r)}, new int[1]{0}, 1);
    M->AddTransformation("mech_move", TT_MOVE, new float[3]{0,0,0});
    M->AddMechanic("mech_move", new float*[2]{(&w2m), (&w2b)}, new int[2]{1,2}, 2);

    M = gameEngine::AddModel("backflap", "../resources/models/verticalflap.obj");
    if (M == nullptr) {cout << "Error: verticalflap Object Not Loaded\n"; exit(1);}
    M->ModelColor = new color(0.780, 0.458, 0, 1);
    M->AddTransformation("init", TT_MOVE, new float[3]{0,0,-90});
    M->AddTransformation("scale", TT_SCALE, new float[3]{0.3,0.3,0.3});
    M->AddTransformation("animatedRotation", TT_ROTATE, new float[4]{0,0,1,0});
    M->AddMechanic("animatedRotation", new float*[1]{(&rot)}, new int[1]{0}, 1);
    M->AddTransformation("place", TT_MOVE, new float[3]{0, 0, 94.9});
    M->AddTransformation("zrotation", TT_ROTATE, new float[4]{0,0,0,1});
    M->AddMechanic("zrotation", new float*[1]{(&zrot)}, new int[1]{0}, 1);
}
