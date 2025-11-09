#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif
#include <string>
#include "raylib.h"
using namespace std;

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Escena Input - Cthulhu");
    SetTargetFPS(60);

    Texture2D cthulhu = LoadTexture("Cthulhito.png");
    SetTextureFilter(cthulhu, TEXTURE_FILTER_BILINEAR);

    Vector2 pos = { 200, 500 };
    float velocidad = 200.0f;

    bool saltando = false;
    float alturaSalto = 80.0f;
    float posBase = pos.y;

    bool mostrarMensaje = true;

    Rectangle boton = { 390, 210, 230, 50 };
    Color colorFondo = DARKGREEN;

    InitAudioDevice();
    Sound sonido = LoadSound("Boing.wav");

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_RIGHT)) pos.x += velocidad * dt;
        if (IsKeyDown(KEY_LEFT))  pos.x -= velocidad * dt;

        if (IsKeyPressed(KEY_SPACE) && !saltando)
        {
            saltando = true;
            PlaySound(sonido);
        }

        if (saltando)
        {
            pos.y = posBase - alturaSalto;
            if (IsKeyReleased(KEY_SPACE))
            {
                pos.y = posBase;
                saltando = false;
            }
        }

        if (IsKeyPressed(KEY_R))
        {
            pos = { 200, 500 };
            posBase = pos.y;
        }

        if (IsKeyPressed(KEY_M))
        {
            mostrarMensaje = !mostrarMensaje;
        }

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, boton))
            {
                colorFondo = Color{
                    (unsigned char)GetRandomValue(20, 255),
                    (unsigned char)GetRandomValue(20, 255),
                    (unsigned char)GetRandomValue(20, 255),
                    255 };
                PlaySound(sonido);
            }
        }

        BeginDrawing();
        ClearBackground(colorFondo);

        DrawTextureEx(cthulhu, pos, 0.0f, 0.4f, WHITE);

        DrawText(TextFormat("Posicion: (%.1f, %.1f)", pos.x, pos.y), 10, screenHeight - 30, 20, YELLOW);

        DrawRectangleRec(boton, GRAY);
        DrawText("El color de la locura", boton.x + 10, boton.y + 15, 20, BLACK);

        if (mostrarMensaje)
        {
            DrawText("Caeras en la Locura", 400, 300, 20, WHITE);
        }

        DrawText("Flechas: mover | SPACE: salto | R: reset | M: mensaje | Click: color de la locura",
            10, 10, 18, LIGHTGRAY);

        EndDrawing();
    }

    UnloadTexture(cthulhu);
    UnloadSound(sonido);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}