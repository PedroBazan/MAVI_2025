#include "RectanguloMovimiento.h"
#include <iostream>
using namespace std;

// Constructor que inicializa la textura, posición, velocidad, ancho y alto del rectángulo

RectanguloMovimiento::RectanguloMovimiento(Texture2D* tex, Vector2 posInicial, Vector2 velInicial) {

	textura = tex;
	posicion = posInicial;
	velocidad = velInicial;
}
RectanguloMovimiento::~RectanguloMovimiento()
{
}

void RectanguloMovimiento::actualizar(float deltaTime)
{
    posicion.x += velocidad.x * deltaTime;
    posicion.y += velocidad.y * deltaTime;

    // Rebote en pantalla
    if (posicion.x < 0 || posicion.x + textura->width > GetScreenWidth())
        velocidad.x *= -1;

    if (posicion.y < 0 || posicion.y + textura->height > GetScreenHeight())
        velocidad.y *= -1;
}
void RectanguloMovimiento::dibujar() const
    {
        DrawTexture(*textura, (int)posicion.x, (int)posicion.y, WHITE);
    }
Vector2 RectanguloMovimiento::getPosicion() const
{
    return posicion;
}   
Vector2 RectanguloMovimiento::getVelocidad() const
    {
        return velocidad;
    }
