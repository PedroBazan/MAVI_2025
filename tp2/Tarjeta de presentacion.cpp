#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector (solo en modo Debug)
#endif
#include "raylib.h"
#include <string>
#include <cstdlib>
#include <ctime>

int main() {
    
    const int screenWidth = 1024;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Movimiento realista - Pedro Bazán");
    SetTargetFPS(60);
    srand(time(NULL));

    
    Vector2 posicion = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 velocidad = { 870.0f, 510.0f }; 
    float radio = 44.0f; 
    int rebotes = 0;

    
    Color colorEsfera = { 255, 0, 255, 150 }; 

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        posicion.x += velocidad.x * deltaTime;
        posicion.y += velocidad.y * deltaTime;

        
        bool rebote = false;

        if (posicion.x - radio <= 0 || posicion.x + radio >= screenWidth) {
            velocidad.x *= -1;
            rebote = true;
        }
        if (posicion.y - radio <= 0 || posicion.y + radio >= screenHeight) {
            velocidad.y *= -1;
            rebote = true;
        }

        //cambiar color
        if (rebote) {
            colorEsfera = {
                (unsigned char)GetRandomValue(50, 255),
                (unsigned char)GetRandomValue(50, 255),
                (unsigned char)GetRandomValue(50, 255),
                150 
            };
            rebotes++;
        }

       
        BeginDrawing();
        ClearBackground(DARKBLUE);

        
        DrawCircleV(posicion, radio, colorEsfera);

        // Textos
        DrawText(TextFormat("Resolución: %d x %d", screenWidth, screenHeight), 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("Posición: (%.1f, %.1f)", posicion.x, posicion.y), 10, 40, 20, YELLOW);
        DrawText(TextFormat("Rebotes: %d", rebotes), 10, 70, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
