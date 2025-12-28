#include "SpriteA.h"

SpriteA::SpriteA()  
{
    textura = LoadTexture("assets/sprite.png");
    posicion = { 100.0f, 100.0f };
}

void SpriteA::Draw() const
{
    DrawTexture(textura, (int)posicion.x, (int)posicion.y, WHITE);
}