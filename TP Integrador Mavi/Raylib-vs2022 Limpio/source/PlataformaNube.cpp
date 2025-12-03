#include "PlataformaNube.h"


PlataformaNube::PlataformaNube(Texture2D* tex, float x, float y, float w, float h, Color c)
{
    rect = { x, y, w, h };
    color = c;
    textura = tex;     // <-- usar el mismo nombre del .h
}

void PlataformaNube::dibujar() const
{
    DrawTexturePro(
        *textura,
        { 0, 0, (float)textura->width, (float)textura->height },
        { rect.x, rect.y, rect.width, rect.height },
        { 0, 0 },
        0,
        WHITE
    );
}
