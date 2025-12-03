#pragma once
#ifndef PLATAFORMA_NUBE_H
#define PLATAFORMA_NUBE_H

#include "raylib.h"

class PlataformaNube {
private:
    Texture2D* textura;   // fijarse porque me da error corregir nombres
public:
    Rectangle rect;
    Color color;

    PlataformaNube(Texture2D* tex, float x, float y, float w, float h, Color c);
    void dibujar() const;

    Rectangle getRect() const { return rect; }
};

#endif