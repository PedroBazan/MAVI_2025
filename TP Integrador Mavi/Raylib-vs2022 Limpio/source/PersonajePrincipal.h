#pragma once
#ifndef PERSONAJEPRINCIPAL_H
#define PERSONAJEPRINCIPAL_H

#include "raylib.h"

class PersonajePrincipal {
private:
    Texture2D* textura;     // Imagen del personaje
    Vector2 posicion;       // Posición
    Vector2 velocidad;      // Velocidad
    bool enElAire;          // Estado de salto

    float gravedad;
    float fuerzaSalto;
    float velocidadMovimiento;

public:
    PersonajePrincipal(Texture2D* tex, Vector2 posInicial);

    void actualizar(float dt, Rectangle piso);
    void dibujar() const;

    Rectangle getRect() const; // Para colisiones
};

#endif

