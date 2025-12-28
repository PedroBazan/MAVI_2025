#include "Proyectil.h"

Proyectil::Proyectil()
{
    posicion = { 0,0 };
    velocidad = { 0,0 };
    activo = false;

    textura = LoadTexture("proyectil.png"); // ✅ sin assets

    radio = (float)textura.width * 0.5f;
}

Proyectil::~Proyectil()
{
    UnloadTexture(textura);
}

void Proyectil::Disparar(Vector2 origen, float anguloDeg, float potencia)
{
    activo = true;
    posicion = origen;

    float t = (anguloDeg - ANGULO_MIN) / (ANGULO_MAX - ANGULO_MIN);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    velocidad.x = potencia * (1.0f - t) * 1.8;
    velocidad.y = -potencia * t * 1.8;
}

void Proyectil::Update(float dt)
{
    if (!activo) return;

    velocidad.y += GRAVEDAD * dt;
    posicion.x += velocidad.x * dt;
    posicion.y += velocidad.y * dt;

    if (posicion.x > ANCHO + 100 || posicion.y > ALTO + 100 || posicion.y < -200)
        activo = false;
}

void Proyectil::Draw() const
{
    if (!activo) return;

    Vector2 pos = { posicion.x - textura.width * 0.5f,
                    posicion.y - textura.height * 0.5f };

    DrawTextureEx(textura, pos, 0.0f, 1.0f, WHITE);
}

bool Proyectil::EstaActivo() const { return activo; }
void Proyectil::Desactivar() { activo = false; }
Vector2 Proyectil::GetPosicion() const { return posicion; }
float Proyectil::GetRadio() const { return radio; }

Rectangle Proyectil::GetRect() const
{
    return {
        posicion.x - textura.width / 2.0f,
        posicion.y - textura.height / 2.0f,
        (float)textura.width,
        (float)textura.height
    };
}