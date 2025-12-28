#include "Enemigo.h"

Enemigo::Enemigo()
{
    tipoMov = MRU_H;
    forma = CIRCULO;

    posicion = { 0,0 };
    velocidad = { 0,0 };

    textura = LoadTexture("enemigo.png"); // sin assets

  
    vivo = false;
    escapo = false;
    tocoSuelo = false;
    escapeConsumido = false;

    // Hitbox
    tam = { (float)textura.width, (float)textura.height };
    float m = (textura.width < textura.height) ? (float)textura.width : (float)textura.height;
    radio = m * 0.5f;
}

Enemigo::~Enemigo()
{
    UnloadTexture(textura);
}

void Enemigo::Inicializar(TipoMovimiento mov, Forma f, Vector2 pos, Vector2 vel)
{
    tipoMov = mov;
    forma = f;
    posicion = pos;
    velocidad = vel;

    vivo = true;
    escapo = false;
    tocoSuelo = false;
    escapeConsumido = false;
    

    // Hitbox del tamaño real del sprite
    tam = { (float)textura.width, (float)textura.height };
    float m = (textura.width < textura.height) ? (float)textura.width : (float)textura.height;
    radio = m * 0.5f;
}

void Enemigo::Update(float dt)
{
    if (!vivo) return;

    // Movimiento
    if (tipoMov == MRU_H)
    {
        posicion.x += velocidad.x * dt * VELOCIDAD_ENEMIGO;
    }
    else if (tipoMov == CAIDA)
    {
        velocidad.y += GRAVEDAD * dt * VELOCIDAD_ENEMIGO;
        posicion.y += velocidad.y * dt * VELOCIDAD_ENEMIGO;
    }
    else if (tipoMov == REBOTE)
    {
        velocidad.y += GRAVEDAD * dt * VELOCIDAD_ENEMIGO;
        posicion.x += velocidad.x * dt * VELOCIDAD_ENEMIGO;
        posicion.y += velocidad.y * dt * VELOCIDAD_ENEMIGO;
    }

    // Bordes laterales
    float halfW = textura.width * 0.5f;
    if (posicion.x + halfW < 0.0f)
    {
        escapo = true;
        vivo = false;
        return;
    }
    if (posicion.x - halfW > (float)ANCHO)
    {
        escapo = true;
        vivo = false;
        return;
    }
    // Suelo
    float bottom = posicion.y + textura.height * 0.5f;
    if (bottom >= SUELO_Y)
    {
        escapo = true;
        vivo = false;
        return;
    }

    // Se va de pantalla
    if (posicion.x > ANCHO + 80 || posicion.y > ALTO + 120)
    {
        escapo = true;
        vivo = false;
    }
}

void Enemigo::Draw() const
{
    if (!vivo) return;

    Vector2 pos = {
        posicion.x - textura.width * 0.5f,
        posicion.y - textura.height * 0.5f
    };

    DrawTextureEx(textura, pos, 0.0f, 1.0f, WHITE); // tamaño original
}

bool Enemigo::ConsumirEscapo()
{
    if (escapo && !escapeConsumido)
    {
        escapeConsumido = true;
        escapo = false;          // 
        return true;
    }
    return false;
}
bool Enemigo::EstaVivo() const { return vivo; }
void Enemigo::Matar() { vivo = false; }


bool Enemigo::ColisionaConCirculo(Vector2 c, float r) const
{
    if (!vivo) return false;

    if (forma == CIRCULO)
    {
        float dx = posicion.x - c.x;
        float dy = posicion.y - c.y;
        float rr = (radio + r);
        return (dx * dx + dy * dy) <= (rr * rr);
    }
    else
    {
        // Rect centrado usando tamaño real del sprite
        Rectangle rec = {
            posicion.x - tam.x * 0.5f,
            posicion.y - tam.y * 0.5f,
            tam.x,
            tam.y
        };
        return CheckCollisionCircleRec(c, r, rec);
    }
}