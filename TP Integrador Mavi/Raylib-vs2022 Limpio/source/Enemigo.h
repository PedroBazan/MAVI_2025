#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

class Enemigo {
private:
    Rectangle rect;
    float velocidad;
    float limiteMin;
    float limiteMax;

    Texture2D* textura;

public:
    Enemigo(Texture2D* tex, float x, float y, float w, float h,
        float vel, float minY, float maxY);

    void actualizar(float dt);
    void dibujar() const;

    Rectangle getRect() const { return rect; }
};

#endif