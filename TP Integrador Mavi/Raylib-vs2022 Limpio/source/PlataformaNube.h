#ifndef PLATAFORMA_NUBE_H
#define PLATAFORMA_NUBE_H

#include "raylib.h"

class PlataformaNube {
public:
    Rectangle rect;
    Color color;
    Texture2D nubeTex = LoadTexture("nube.png");

    PlataformaNube(float x, float y, float w, float h, Color c);
    void dibujar() const;
};

#endif