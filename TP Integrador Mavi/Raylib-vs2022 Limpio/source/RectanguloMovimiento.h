#pragma once // Directiva para asegurar que el archivo solo se incluya una vez
#ifndef RECTANGULOMOVIMIENTO_H
#define RECTANGULOMOVIMIENTO_H
#include "raylib.h"
#include "PlataformaNube.h"
using namespace std;

class RectanguloMovimiento{
private:
	Texture2D* textura; // Textura del rectángulo
	Vector2 posicion;  // Posición del rectángulo
	Vector2 velocidad; // Velocidad de movimiento del rectángulo
	

public: 
	// Constructor que inicializa la textura, posición, velocidad, ancho y alto del rectángulo
	RectanguloMovimiento(Texture2D* tex, Vector2 posInicial, Vector2 velInicial);
	// Destructor
	~RectanguloMovimiento();
	//colisiones con las plataformas
	void actualizar(float dt, const PlataformaNube* plataformas, int cantPlataformas);
	// Método para dibujar el rectángulo en la pantalla
	void dibujar() const;
	// Métodos para obtener información (Getters)
	Vector2 getPosicion() const;
	Vector2 getVelocidad() const;
	Rectangle getRect() const;
	float getAncho() const { return (float)textura->width; }
	float getAlto()  const { return (float)textura->height; }

};
#endif // RECTANGULOMOVIMIENTO_H


