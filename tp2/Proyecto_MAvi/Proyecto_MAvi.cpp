#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif
#include <string>
#include "raylib.h"
using namespace std;

int main() {

    InitWindow(800, 450, "Tarjeta de Presentación");
    SetTargetFPS(60);


    Color fondo = DARKBLUE;
    bool mostrarMensaje2 = false;


    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            mostrarMensaje2 = !mostrarMensaje2;// funcion switch usada para alternar entre dos estados
        }

        BeginDrawing();
        ClearBackground(fondo);


        DrawText("Pedro Bazán", 300, 100, 40, RAYWHITE);


        DrawCircle(400, 250, 50, PURPLE);


        if (mostrarMensaje2) {
            DrawText("Primer trabajo en raylib", 300, 350, 20, GREEN);
        }
        else {
            DrawText("Colores y ventanas", 300, 350, 20, YELLOW);
        }


        DrawText("Presiona espacio para cambiar el mensaje", 10, 420, 15, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}