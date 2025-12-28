#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector
#endif

#include <vector>
using namespace std;

#include "raylib.h"
#include "ConfigJuego.h"
#include "Jugador.h"
#include "Proyectil.h"
#include "Enemigo.h"

int main()
{
    InitWindow(800, 600, "tp 6");
    SetTargetFPS(60);

    Texture2D fondo = LoadTexture("FondoJuego.png");

    Jugador jugador;
    Proyectil proyectil;

    const int MAX_ENEMIGOS = 60;
    vector<Enemigo> enemigos(MAX_ENEMIGOS);

    float spawnTimer = 0.0f;
    float spawnInterval = 1.0f;
    int spawnIndex = 0;

    int puntaje = 0;
    int vidas = VIDAS_INICIALES;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // INPUT
        jugador.UpdateInput();

        if (IsKeyPressed(KEY_SPACE) && !proyectil.EstaActivo() && vidas > 0)
        {
            proyectil.Disparar(
                jugador.GetPosicion(),
                jugador.GetAnguloDeg(),
                jugador.GetPotencia()
            );
        }

        // SPAWN
        if (vidas > 0)
        {
            spawnTimer += dt;

            if (spawnTimer >= spawnInterval)
            {
                spawnTimer = 0.0f;

                for (int i = 0; i < enemigos.size(); i++)
                {
                    if (!enemigos[i].EstaVivo())
                    {
                        if (spawnIndex % 3 == 0)
                        {
                            enemigos[i].Inicializar(
                                Enemigo::MRU_H, Enemigo::RECTANGULO,
                                { (float)ANCHO + 50, 150 }, { -200, 0 }
                            );
                        }
                        else if (spawnIndex % 3 == 1)
                        {
                            enemigos[i].Inicializar(
                                Enemigo::CAIDA, Enemigo::CIRCULO,
                                { 400, -40 }, { 0, 0 }
                            );
                        }
                        else
                        {
                            enemigos[i].Inicializar(
                                Enemigo::REBOTE, Enemigo::CIRCULO,
                                { 650, 100 }, { -120, 0 }
                            );
                        }

                        spawnIndex++;
                        break;
                    }
                }
            }
        }

        // UPDATE
        if (vidas > 0)
            proyectil.Update(dt);

        bool vidaRestadaEsteFrame = false; // revisar porque baja 2 vidas en el segundo enemigo

        for (int i = 0; i < enemigos.size(); i++)
        {
            if (vidas > 0)
                enemigos[i].Update(dt);

            if (vidas > 0 && proyectil.EstaActivo() && enemigos[i].EstaVivo())
            {
                if (enemigos[i].ColisionaConCirculo(proyectil.GetPosicion(), proyectil.GetRadio()))
                {
                    enemigos[i].Matar();
                    proyectil.Desactivar();
                    puntaje += 10;
                }
            }

            if (!vidaRestadaEsteFrame && enemigos[i].ConsumirEscapo())
            {
                if (vidas > 0) vidas--;
                vidaRestadaEsteFrame = true;
            }
        }

        // dibujo
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float scaleX = (float)ANCHO / (float)fondo.width;
        float scaleY = (float)ALTO / (float)fondo.height;
        float scale = (scaleX > scaleY) ? scaleX : scaleY;
        DrawTextureEx(fondo, { 0.0f, 0.0f }, 0.0f, scale, WHITE);

        DrawRectangle(0, (int)SUELO_Y, ANCHO, ALTO, DARKGREEN);

        for (int i = 0; i < enemigos.size(); i++)
            enemigos[i].Draw();

        jugador.Draw();
        proyectil.Draw();
        jugador.DrawHUD(puntaje, vidas);

        if (vidas <= 0)
            DrawText("GAME OVER", 300, 280, 40, RED);

        EndDrawing();
    }

    UnloadTexture(fondo);
    CloseWindow();
    return 0;
}