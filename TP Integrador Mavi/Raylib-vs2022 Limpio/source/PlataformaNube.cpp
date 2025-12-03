#include "PlataformaNube.h"

PlataformaNube::PlataformaNube(float x, float y, float w, float h, Color c) {
    rect = { x, y, w, h };
    color = c;
}

void PlataformaNube::dibujar() const {
    DrawTexture(nubeTex, rect.x, rect.y, WHITE);

}