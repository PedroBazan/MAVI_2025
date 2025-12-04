#include "RectanguloMovimiento.h"
#include "raylib.h"

// Constructor modificado para dar ancho y alto
RectanguloMovimiento::RectanguloMovimiento(Texture2D* tex, Vector2 posInicial, Vector2 velInicial, float w, float h)
{
    textura = tex;
    posicion = posInicial;
    velocidad = velInicial;
    ancho = w;
    alto = h;
}

RectanguloMovimiento::~RectanguloMovimiento()
{
}

// Actualización: movimiento + colisiones
void RectanguloMovimiento::actualizar(float deltaTime, const PlataformaNube* plataformas, int cantPlataformas)
{
    posicion.x += velocidad.x * deltaTime;
    posicion.y += velocidad.y * deltaTime;

    Rectangle rectNube = getRect();

    // Rebote con nubes estáticas
    for (int i = 0; i < cantPlataformas; i++)
    {
        if (CheckCollisionRecs(rectNube, plataformas[i].getRect()))
        {
            velocidad.x *= -1;
            rectNube = getRect();
        }
    }

    // Rebote contra bordes de pantalla
    if (posicion.x < 0 || posicion.x + textura->width > GetScreenWidth())
        velocidad.x *= -1;

    if (posicion.y < 0 || posicion.y + textura->height > GetScreenHeight())
        velocidad.y *= -1;
}
//reiniciar
void RectanguloMovimiento::reiniciar(Vector2 posInicial, Vector2 velInicial)
{
    posicion = posInicial;
    velocidad = velInicial;
}

// Dibujo
void RectanguloMovimiento::dibujar() const
{
    DrawTexturePro(
        *textura,
        { 0, 0, (float)textura->width, (float)textura->height },   // parte que recorta
        { posicion.x, posicion.y, ancho, alto },                   // destino con escala
        { 0, 0 },
        0,
        WHITE
    );
}


Rectangle RectanguloMovimiento::getRect() const
{
    return { posicion.x, posicion.y, ancho, alto };
}

Vector2 RectanguloMovimiento::getPosicion() const { return posicion; }
Vector2 RectanguloMovimiento::getVelocidad() const { return velocidad; }