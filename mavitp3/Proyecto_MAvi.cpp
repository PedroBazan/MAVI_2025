#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif
#include <string>
#include "raylib.h"
using namespace std;

int main() {
    
    const int screenWidth = 1024;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Sprite - Cthulhu");

    SetTargetFPS(60);

    Texture2D textura = LoadTexture("Cthulhito.png");
    SetTextureFilter(textura, TEXTURE_FILTER_BILINEAR);
    
    //sprite 1
    Vector2 pos1 = { 200.0f, 300.0f };
    float escala1 = 0.4f;
    float rot1 = 0.0f;
    Color color1 = WHITE;

    //sprite 2
    Vector2 pos2 = { 700.0f, 300.0f };
    float escala2 = 0.7f;
    float rot2 = 15.0f;
    Color color2 = GREEN;

    // Control
    bool intercambiar = false;
    Vector2 velocidad = { 100.0f, 80.0f };
    Vector2 dir = { 4, 1 };

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        //Movimiento
        pos1.x += velocidad.x * dir.x * delta;
        pos1.y += velocidad.y * dir.y * delta;

       
        if (pos1.x < 0 || pos1.x + textura.width * escala1 > screenWidth) dir.x *= -1;
        if (pos1.y < 0 || pos1.y + textura.height * escala1 > screenHeight) dir.y *= -1;

        
        if (IsKeyDown(KEY_RIGHT)) pos2.x += 200 * delta;
        if (IsKeyDown(KEY_LEFT)) pos2.x -= 200 * delta;
        if (IsKeyDown(KEY_UP)) pos2.y -= 200 * delta;
        if (IsKeyDown(KEY_DOWN)) pos2.y += 200 * delta;

        
        if (IsKeyPressed(KEY_SPACE)) {
            intercambiar = !intercambiar;

            if (intercambiar) {
                swap(escala1, escala2);
                swap(color1, color2);
                swap(rot1, rot2);
            }
            else {
                swap(escala1, escala2);
                swap(color1, color2);
                swap(rot1, rot2);
            }
        }

        // Funcion
        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawTextureEx(textura, pos1, rot1, escala1, color1);
        DrawTextureEx(textura, pos2, rot2, escala2, color2);

        DrawText("Sprites de Cthulhu - Ejemplo Raylib", 10, 10, 25, RAYWHITE);

        DrawText(TextFormat("Sprite 1 -> Pos(%.0f, %.0f) Escala: %.2f Rot: %.1f", pos1.x, pos1.y, escala1, rot1),
            10, 50, 20, color1);
        DrawText(TextFormat("Sprite 2 -> Pos(%.0f, %.0f) Escala: %.2f Rot: %.1f", pos2.x, pos2.y, escala2, rot2),
            10, 80, 20, color2);

        DrawText("Presiona ESPACIO para intercambiar estilos", 10, 120, 20, YELLOW);
        DrawText("Usa flechas para mover al Cthulhu derecho", 10, 150, 20, LIGHTGRAY);

        EndDrawing();
    }

    UnloadTexture(textura);
    CloseWindow();
    return 0;
}