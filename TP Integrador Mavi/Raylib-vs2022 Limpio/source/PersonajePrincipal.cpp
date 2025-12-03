#include "PersonajePrincipal.h"
#include "PlataformaNube.h"


PersonajePrincipal::PersonajePrincipal(Texture2D* tex, Vector2 posInicial)
{
    textura = tex;
    posicion = posInicial;
    velocidad = { 0, 0 };
    enElAire = false;

    gravedad = 900.0f;
    fuerzaSalto = -550.0f;
    velocidadMovimiento = 250.0f;
}

void PersonajePrincipal::actualizar(float dt, Rectangle piso, const PlataformaNube* plataformas, int cantPlataformas)
{
    //Movimiento horizontal
    if (IsKeyDown(KEY_D)) velocidad.x = velocidadMovimiento;
    else if (IsKeyDown(KEY_A)) velocidad.x = -velocidadMovimiento;
    else velocidad.x = 0;

    //salto
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
    enElAire = true;

    if (CheckCollisionRecs(rectJugador, piso)) {
        posicion.y = piso.y - textura->height;
        velocidad.y = 0;
        enElAire = false;
    }
    //Colisión con plataformas
    for (int i = 0; i < cantPlataformas; i++) {
        Rectangle nube = plataformas[i].getRect();

        if (CheckCollisionRecs(getRect(), nube)) {

            // Solo colisionamos si venimos cayendo
            if (velocidad.y > 0 && rectJugador.y + rectJugador.height <= nube.y + 10) {
                posicion.y = nube.y - textura->height;
                velocidad.y = 0;
                enElAire = false;
            }
        }
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