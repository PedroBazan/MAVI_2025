#include "Enemigo.h"

Enemigo::Enemigo(Texture2D* tex, float x, float y, float w, float h,
    float vel, float minY, float maxY)
{
    textura = tex;
    rect = { x, y, w, h };
    velocidad = vel;
    limiteMin = minY;
    limiteMax = maxY;
}

void Enemigo::actualizar(float dt)
{
    rect.y += velocidad * dt;

    // Rebote con el límite superior
    if (rect.y < limiteMin) {
        rect.y = limiteMin;
        velocidad *= -1;
    }
    // Rebote con límite inferior
    else if (rect.y + rect.height > limiteMax) {
        rect.y = limiteMax - rect.height;
        velocidad *= -1;
    }
}

void Enemigo::dibujar() const
{
    DrawTexturePro(
        *textura,
        { 0, 0, (float)textura->width, (float)textura->height },
        rect,
        { 0, 0 },
        0,
        WHITE
    );
}