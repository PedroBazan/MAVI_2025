#include "Jugador.h"

#include "Jugador.h"

Jugador::Jugador()
{
    posicion = { 60.0f, SUELO_Y - 30.0f };
    anguloDeg = 45.0f;
    potencia = 360.0f;

    textura = LoadTexture("jugador.png"); 
}

Jugador::~Jugador()
{
    UnloadTexture(textura);
}

void Jugador::UpdateInput()
{
    if (IsKeyDown(KEY_UP))   anguloDeg += ANGULO_STEP;
    if (IsKeyDown(KEY_DOWN)) anguloDeg -= ANGULO_STEP;

    if (anguloDeg < ANGULO_MIN) anguloDeg = ANGULO_MIN;
    if (anguloDeg > ANGULO_MAX) anguloDeg = ANGULO_MAX;

    if (IsKeyDown(KEY_RIGHT)) potencia += POTENCIA_STEP * GetFrameTime();
    if (IsKeyDown(KEY_LEFT))  potencia -= POTENCIA_STEP * GetFrameTime();

    if (potencia < POTENCIA_MIN) potencia = POTENCIA_MIN;
    if (potencia > POTENCIA_MAX) potencia = POTENCIA_MAX;
}

void Jugador::Draw() const
{
    Vector2 pos = { posicion.x - textura.width * 0.5f,
                    posicion.y - textura.height * 0.5f };

    DrawTextureEx(textura, pos, 0.0f, 1.0f, WHITE);
}

void Jugador::DrawHUD(int puntaje, int vidas) const
{
    DrawText(TextFormat("Puntaje: %d", puntaje), 15, 15, 20, BLACK);
    DrawText(TextFormat("Vidas: %d", vidas), 15, 40, 20, BLACK);
    DrawText(TextFormat("Angulo: %.0f", anguloDeg), 15, 65, 20, BLACK);
    DrawText(TextFormat("Potencia: %.0f", potencia), 15, 90, 20, BLACK);

    float t = (anguloDeg - ANGULO_MIN) / (ANGULO_MAX - ANGULO_MIN);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    Vector2 dir = { 1.0f - t, -t };
    Vector2 fin = { posicion.x + 60.0f * dir.x, posicion.y + 60.0f * dir.y };
    DrawLine((int)posicion.x, (int)posicion.y, (int)fin.x, (int)fin.y, DARKBLUE);
}

Vector2 Jugador::GetPosicion() const { return posicion; }
float Jugador::GetAnguloDeg() const { return anguloDeg; }
float Jugador::GetPotencia() const { return potencia; }