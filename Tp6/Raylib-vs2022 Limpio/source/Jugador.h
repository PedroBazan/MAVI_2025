#pragma once
#include "raylib.h"
#include "ConfigJuego.h"

class Jugador
{
private:
    Vector2 posicion;   // fijo
    float anguloDeg;    // apuntado
    float potencia;     // "aceleración inicial" / potencia del disparo
    Texture2D textura;

public:
    Jugador();
    ~Jugador(); 

    void Draw() const;
    void UpdateInput(); // EVENT
    void DrawHUD(int puntaje, int vidas) const;

    Vector2 GetPosicion() const;
    float GetAnguloDeg() const;
    float GetPotencia() const;
};
