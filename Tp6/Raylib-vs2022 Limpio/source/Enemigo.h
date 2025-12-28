#pragma once
#include "raylib.h"
#include "ConfigJuego.h"

class Enemigo
{
public:
    enum TipoMovimiento { MRU_H, CAIDA, REBOTE };
    enum Forma { CIRCULO, RECTANGULO };

private:
    TipoMovimiento tipoMov;
    Forma forma;

    Vector2 posicion;
    Vector2 velocidad;

    Texture2D textura;

    Vector2 tam;   // rect
    float radio;   // circulo

    bool vivo;
    bool escapo;
    bool tocoSuelo;
    bool escapeConsumido;

public:
    Enemigo();
    ~Enemigo();

    void Inicializar(TipoMovimiento mov, Forma f, Vector2 pos, Vector2 vel);
    void Update(float dt);
    void Draw() const;

    bool EstaVivo() const;
    void Matar();

    bool ConsumirEscapo();

    bool ColisionaConCirculo(Vector2 c, float r) const;
};
