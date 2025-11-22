#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif

#include "raylib.h"

int main(void)
{
    // Inicializamos una ventana de 800x450 píxeles con un título personalizado
    InitWindow(800, 450, "Proyecto MAVI");

    // Configuramos el framerate deseado (opcional, pero recomendado)
    SetTargetFPS(60);

    Color fondo = { 110, 100, 215, 255 };//color violeta personalizado
    Color texto = DARKPURPLE;

    // Bucle principal del juego (se repite hasta que se cierre la ventana)
    while (!WindowShouldClose())
    {
        // Iniciamos la etapa de dibujo
        BeginDrawing();

        // Limpiamos la pantalla 
        ClearBackground(fondo);

		// Dibujamos un texto centrado, aca damos la posicion, el tamaño y el color
        DrawText("Felicitaciones, ejecutaste tu primer proyecto con Raylib!!!", 90, 200, 20, texto);

        // Dibujamos un rectángulo a modo decorativo
        DrawRectangle(80, 190, 650, 40, Fade(DARKGREEN, 0.5f)); // Fondo semitransparente para resaltar el texto

        // Finalizamos el dibujo
        EndDrawing();
    }

    // Cerramos la ventana y liberamos recursos
    CloseWindow();

    return 0;
}

