#pragma once
#include "raylib.h"

class SpriteA
{
private:
    Texture2D textura;
    Vector2 posicion;

public:
    SpriteA();
    void Draw() const;
};
