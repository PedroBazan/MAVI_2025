#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif
#include <string>
#include "raylib.h"
#include "RectanguloMovimiento.h"
using namespace std;

int main(void)
{
    // Inicializamos una ventana de hd píxeles con un título personalizado
    InitWindow(1280, 720, "Trabajo de MAVI");

    // Configuramos el framerate deseado (opcional, pero recomendado)
    SetTargetFPS(60);

    Color fondo = { 0, 255, 0, 1 };//color violeta personalizado
    Color texto = DARKPURPLE;  // color de texto personalizado
   
    //Cargo el fondo de una imagen
    Texture2D fondoImagen = LoadTexture("FondoJuego.png");
	Texture2D Nube = LoadTexture("Nube.png");
    SetTextureFilter(fondoImagen, TEXTURE_FILTER_BILINEAR);
    

    RectanguloMovimiento rect(&Nube, { 200, 200 }, { 150, 80 });

    

    // Bucle principal del juego (se repite hasta que se cierre la ventana)
    while (!WindowShouldClose())
    {
        // Agrego letra P para cerrar el programa
        if (IsKeyPressed(KEY_P)) {
            CloseWindow();
                break;
        }  
        
        float dt = GetFrameTime();  // obligatorio para movimiento realista
        rect.actualizar(dt);        // ? ACTUALIZA LA NUBE
        // Iniciamos la etapa de dibujo
        BeginDrawing();


        // insertamos la imagen de fondo
		DrawTexture(fondoImagen, 0, 0, WHITE);
        rect.dibujar();

		

        // Finalizamos el dibujo
        EndDrawing();
    }
	// descargo la textura de la imagen
    UnloadTexture(fondoImagen);
    UnloadTexture(Nube);


    // Cerramos la ventana y liberamos recursos
    CloseWindow();

    return 0;
}

