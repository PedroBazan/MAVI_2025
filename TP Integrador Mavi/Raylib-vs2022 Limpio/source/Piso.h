#pragma once
#ifndef PISO_H
#define PISO_H

#include "raylib.h"

class Piso {
private:
    Rectangle rect;
    Color color;

public:
    Piso(float x, float y, float ancho, float alto, Color color);

    void dibujar() const;
    float getY() const { return rect.y; }
    float getAlto() const { return rect.height; }
    Rectangle getRect() const { return rect; }
};

#endif