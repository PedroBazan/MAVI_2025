#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif
#include <string>
#include "raylib.h"
using namespace std;

int main(void)
{
    // Inicializamos una ventana de hd píxeles con un título personalizado
    InitWindow(1280, 720, "Trabajo de MAVI");

    // Configuramos el framerate deseado (opcional, pero recomendado)
    SetTargetFPS(60);

    Color fondo = { 0, 255, 0, 1 };//color violeta personalizado
    Color texto = DARKPURPLE;
    //Cargo el fondo de una imagen

    Texture2D fondoImagen = LoadTexture("FondoJuego.png");
    SetTextureFilter(fondoImagen, TEXTURE_FILTER_BILINEAR);


    // alternar mensajes
    bool mostrarMensaje2 = false;

    // Bucle principal del juego (se repite hasta que se cierre la ventana)
    while (!WindowShouldClose())
    {
        // Agrego letra P para cerrar el programa
        if (IsKeyPressed(KEY_P)) {
            CloseWindow();
                break;
        }
                
        
        if (IsKeyPressed(KEY_SPACE)) {
            mostrarMensaje2 = !mostrarMensaje2;// funcion switch usada para alternar entre dos estados
		}
        // Iniciamos la etapa de dibujo
        BeginDrawing();

        // insertamos la imagen de fondo
		DrawTexture(fondoImagen, 0, 0, WHITE);

		// Dibujamos un texto centrado, aca damos la posicion, el tamaño y el color
        if (mostrarMensaje2) {
            DrawText("Felicitaciones, ejecutaste tu primer proyecto con Raylib!!!", 350, 360, 20, texto);
            DrawRectangle(350, 360, 588, 20, Fade(DARKGREEN, 0.5f));
        }
        else {
            DrawText("Estas rapasando la unidad 1? ", 350, 360, 20, DARKBLUE);
            DrawRectangle(350, 360, 388, 20, Fade(MAGENTA, 0.5f));

		}

        // Dibujamos un rectángulo a modo decorativo
         // Fondo semitransparente para resaltar el texto

        // Finalizamos el dibujo
        EndDrawing();
    }
	// descargo la textura de la imagen
    UnloadTexture(fondoImagen);


    // Cerramos la ventana y liberamos recursos
    CloseWindow();

    return 0;
}

