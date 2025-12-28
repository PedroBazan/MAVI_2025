#pragma once
#include "raylib.h"
#include "ConfigJuego.h"

class Proyectil
{
private:
    Vector2 posicion;
    Vector2 velocidad;
    float radio;
    bool activo;
    Texture2D textura;   

public:
    Proyectil();
    ~Proyectil();        

    void Disparar(Vector2 origen, float anguloDeg, float potencia);
    void Update(float dt);
    void Draw() const;

    bool EstaActivo() const;
    void Desactivar();

    Vector2 GetPosicion() const;
    float GetRadio() const;

    // ver para la colision

    Rectangle GetRect() const;
};