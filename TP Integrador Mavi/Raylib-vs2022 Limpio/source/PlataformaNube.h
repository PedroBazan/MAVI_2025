#pragma once
#ifndef PLATAFORMA_NUBE_H
#define PLATAFORMA_NUBE_H

#include "raylib.h"

class PlataformaNube {
private:
    Texture2D* textura;   // <-- nombre correcto en ambos archivos
public:
    Rectangle rect;
    Color color;

    PlataformaNube(Texture2D* tex, float x, float y, float w, float h, Color c);
    void dibujar() const;

    Rectangle getRect() const { return rect; }
};

#endif