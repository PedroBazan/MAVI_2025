#include "PersonajePrincipal.h"
#include "PlataformaNube.h"


PersonajePrincipal::PersonajePrincipal(Texture2D* tex, Vector2 posInicial)
{
    textura = tex;
    posicion = posInicial;
    velocidad = { 0, 0 };
    enElAire = false;

    gravedad = 900.0f;
    fuerzaSalto = -620.0f;
    velocidadMovimiento = 250.0f;
    ancho = textura->width * 1.0f;
    alto = textura->height * 1.0f;
}

void PersonajePrincipal::actualizar(float dt, Rectangle piso, const PlataformaNube* plataformas, int cantPlataformas, Rectangle rectNubeMov)
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
        posicion.y = piso.y - alto;
        velocidad.y = 0;
        enElAire = false;
    }
    rectJugador = getRect(); // por las dudas, lo recalculamos

    //colision con la nube que se mueve

    if (CheckCollisionRecs(rectJugador, rectNubeMov)) {
        // ver porque solo cuando caigo

        if (velocidad.y > 0 && rectJugador.y + rectJugador.height <= rectNubeMov.y + 10) {
            posicion.y = rectNubeMov.y - alto;
            velocidad.y = 0;
            enElAire = false;
        }
    }
    //Colisión con plataformas
    for (int i = 0; i < cantPlataformas; i++) {
        Rectangle nube = plataformas[i].getRect();

        if (CheckCollisionRecs(getRect(), nube)) {

            // Solo colisionamos si venimos cayendo
            if (velocidad.y > 0 && rectJugador.y + rectJugador.height <= nube.y + 10) {
                posicion.y = nube.y - alto;
                velocidad.y = 0;
                enElAire = false;
            }
        }
    }
}

void PersonajePrincipal::dibujar() const
{
    DrawTexturePro(
        *textura,
        { 0,0,(float)textura->width,(float)textura->height },
        { posicion.x, posicion.y, ancho, alto },
        { 0,0 },
        0,
        WHITE
    );

}

Rectangle PersonajePrincipal::getRect() const {
    return { posicion.x, posicion.y, ancho, alto };
}