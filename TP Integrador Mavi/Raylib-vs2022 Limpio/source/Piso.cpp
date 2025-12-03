#include "Piso.h"

Piso::Piso(float x, float y, float ancho, float alto, Color c) {
    rect = { x, y, ancho, alto };
    color = c;
}

void Piso::dibujar() const {
    DrawRectangleRec(rect, color);
}