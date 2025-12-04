#pragma once
#ifndef PERSONAJEPRINCIPAL_H
#define PERSONAJEPRINCIPAL_H

#include "raylib.h"
#include "PlataformaNube.h"

class PersonajePrincipal {
private:
    Texture2D* textura;     // Imagen del personaje
    Vector2 posicion;       // Posición
    Vector2 velocidad;      // Velocidad
    bool enElAire;          // Estado de salto

    float gravedad;
    float fuerzaSalto;
    float velocidadMovimiento;
    float ancho;  
    float alto;

public:

    PersonajePrincipal(Texture2D* tex, Vector2 posInicial);

    void reiniciar(Vector2 posInicial); //  para reiniciar una vez que perdio. 

    void actualizar(float dt, Rectangle piso,
        const PlataformaNube* plataformas, int cantPlataformas,
        Rectangle rectNubeMov); // colisiones agregada la nube que se mueve
    void dibujar() const;

    Rectangle getRect() const; // Para colisiones
};

#endif

