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
void PersonajePrincipal::reiniciar(Vector2 posInicial) // para reiniciar
{
    posicion = posInicial;
    velocidad = { 0, 0 };
    enElAire = false;
}

void PersonajePrincipal::actualizar(float dt, Rectangle piso,const PlataformaNube* plataformas, int cantPlataformas, Rectangle rectNubeMov, Sound sonidoSalto)
{
    // Movimiento horizontal
    if (IsKeyDown(KEY_D))      velocidad.x = velocidadMovimiento;
    else if (IsKeyDown(KEY_A)) velocidad.x = -velocidadMovimiento;
    else                       velocidad.x = 0;

    // Salto
    if (IsKeyPressed(KEY_SPACE) && !enElAire) {
        velocidad.y = fuerzaSalto;
        enElAire = true;

        PlaySound(sonidoSalto);
    }

    // Gravedad
    velocidad.y += gravedad * dt;

    // Movimiento
    posicion.x += velocidad.x * dt;
    posicion.y += velocidad.y * dt;


    // y si pisa alguna nube lo ponemos en false
    enElAire = true;

    // Rect�ngulo del jugador para colisiones
    Rectangle rectJugador = getRect();

    // --- Colisi�n con la nube que se mueve ---
    if (CheckCollisionRecs(rectJugador, rectNubeMov)) {
        bool caeDesdeArriba =
            (velocidad.y > 0) &&
            (rectJugador.y + rectJugador.height <= rectNubeMov.y + 3);

        if (caeDesdeArriba) {
            posicion.y = rectNubeMov.y - alto;
            velocidad.y = 0;
            enElAire = false;
            rectJugador = getRect(); // recalculamos por las dudas
        }
    }

    // --- Colisi�n con plataformas est�ticas ---
    for (int i = 0; i < cantPlataformas; i++) {
        Rectangle nube = plataformas[i].getRect();
        rectJugador = getRect(); // por si ajustamos antes

        if (CheckCollisionRecs(rectJugador, nube)) {
            bool caeDesdeArriba =
                (velocidad.y > 0) &&
                (rectJugador.y + rectJugador.height <= nube.y + 3);

            if (caeDesdeArriba) {
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