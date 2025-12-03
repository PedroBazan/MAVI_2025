#include "PersonajePrincipal.h"

PersonajePrincipal::PersonajePrincipal(Texture2D* tex, Vector2 posInicial)
{
    textura = tex;
    posicion = posInicial;
    velocidad = { 0, 0 };
    enElAire = false;

    gravedad = 900.0f;
    fuerzaSalto = -450.0f;
    velocidadMovimiento = 250.0f;
}

void PersonajePrincipal::actualizar(float dt, Rectangle piso)
{
    // --- Movimiento horizontal ---
    if (IsKeyDown(KEY_D)) velocidad.x = velocidadMovimiento;
    else if (IsKeyDown(KEY_A)) velocidad.x = -velocidadMovimiento;
    else velocidad.x = 0;

    // --- Salto ---
    if (IsKeyPressed(KEY_SPACE) && !enElAire) {
        velocidad.y = fuerzaSalto;
        enElAire = true;
    }

    // Gravedad
    velocidad.y += gravedad * dt;

    // Movimiento
    posicion.x += velocidad.x * dt;
    posicion.y += velocidad.y * dt;

    // Colisión con el piso
    Rectangle rectJugador = getRect();

    if (CheckCollisionRecs(rectJugador, piso)) {
        posicion.y = piso.y - textura->height;
        velocidad.y = 0;
        enElAire = false;
    }
}

void PersonajePrincipal::dibujar() const
{
    DrawTexture(*textura, posicion.x, posicion.y, WHITE);
}

Rectangle PersonajePrincipal::getRect() const
{
    return { posicion.x, posicion.y,
             (float)textura->width, (float)textura->height };
}