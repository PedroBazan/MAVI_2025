#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif
#include <string>
#include "raylib.h"
#include "PlataformaNube.h"
#include "RectanguloMovimiento.h"
#include "Piso.h"
#include "PersonajePrincipal.h"

using namespace std;

int main(void)
{
    // Inicializamos una ventana de hd píxeles con un título personalizado
    InitWindow(1280, 720, "Trabajo de MAVI Integrador");

    // Configuramos el framerate deseado (opcional, pero recomendado)
    SetTargetFPS(60);

    Color fondo = { 0, 255, 0, 1 };//color violeta personalizado
    Color texto = DARKPURPLE;  // color de texto personalizado
   
    //Cargo el fondo de una imagen
    Texture2D fondoImagen = LoadTexture("FondoJuego.png");
    Texture2D texturaNube = LoadTexture("Nube.png");
    Texture2D texJugador = LoadTexture("Cthulhito.png");
    SetTextureFilter(fondoImagen, TEXTURE_FILTER_BILINEAR);

    // Crear piso
    Rectangle piso = { 0, 650, 1280, 70 };
    Piso pisoVisual(0, 650, 1280, 70, GREEN);
    
    // Crear personaje
    PersonajePrincipal jugador(&texJugador, { 200, 200 });

    // nube voladora
    RectanguloMovimiento rect(&texturaNube, { 200, 200 }, { 350, 180 }, 120, 60);

    //nubes quietas (hice un array para simplificar)
    PlataformaNube plataformas[] = {
    PlataformaNube(&texturaNube, 200, 500, 120, 40, WHITE),
   // PlataformaNube(&texturaNube, 400, 400, 120, 40, WHITE), desactivada para darle dificultad
    PlataformaNube(&texturaNube, 800, 500, 120, 40, WHITE),
    PlataformaNube(&texturaNube, 650, 120, 120, 40, WHITE),
    PlataformaNube(&texturaNube, 1040, 120, 120, 40, WHITE)
    };
    int cantPlataformas = sizeof(plataformas) / sizeof(plataformas[0]);

    //condicion de gameover
    bool perdiste = false;

    

    // Bucle principal del juego (se repite hasta que se cierre la ventana)
    while (!WindowShouldClose())
    {
        // Agrego letra P para cerrar el programa
        if (IsKeyPressed(KEY_P)) {
            CloseWindow();
                break;
        }  
        
        float dt = GetFrameTime();  // obligatorio para movimiento

        if (!perdiste) {
            // Actualizo nube en movimiento y jugador SOLO si no perdiste
            rect.actualizar(dt, plataformas, cantPlataformas);

            jugador.actualizar(
                dt,
                piso,
                plataformas,
                cantPlataformas,
                rect.getRect() 
            );

            // si el jugador toca el piso -> GAME OVER
            Rectangle rectJugador = jugador.getRect();
            float bottomJugador = rectJugador.y + rectJugador.height;

            if (bottomJugador >= piso.y) {
                perdiste = true;
            }
        }




        // Iniciamos la etapa de dibujo
        BeginDrawing();

        ClearBackground(BLACK); // limpio la pantalla antes de dibujar


        // insertamos la imagen de fondo me guie con la ia para poder hacerlo a escala y que se vea bien porque no me salia del tamaño de la ventana
        float scaleX = (float)GetScreenWidth() / fondoImagen.width;
        float scaleY = (float)GetScreenHeight() / fondoImagen.height;
        float scale = (scaleX > scaleY) ? scaleX : scaleY;

        DrawTextureEx(fondoImagen, { 0, 0 }, 0, scale, WHITE); //  dibujo fondo
        pisoVisual.dibujar(); // dibujo piso
        jugador.dibujar();// dibujo personaje
		rect.dibujar(); // dibujo la nube movimiento

        // dibujo nubes estaticas en array
        for (int i = 0; i < cantPlataformas; i++)
            plataformas[i].dibujar();



		// Dibujamos textos informativos en pantalla
        DrawText(TextFormat("Resolucion: %dx%d", GetScreenWidth(), GetScreenHeight()), 10, 10, 20, BLACK);
        DrawText("mover-> D, mover <- A, Espacio salta, P para salir", 250, 10, 20, BLACK);
        DrawText(TextFormat("Jugador X: %.1f Y: %.1f", jugador.getRect().x, jugador.getRect().y), 10, 40, 20, BLACK);
        // mensaje de game over
        if (perdiste) {
            const char* mensaje = "PERDISTE!";
            int fontSize = 60;
            int textWidth = MeasureText(mensaje, fontSize);
            int x = GetScreenWidth() / 2 - textWidth / 2;
            int y = GetScreenHeight() / 2 - fontSize / 2;
            DrawText(mensaje, x, y, fontSize, RED);
        }

        // Finalizamos el dibujo
        EndDrawing();
    }
	// descargo la textura de la imagen
    UnloadTexture(fondoImagen);
    UnloadTexture(texturaNube);
    UnloadTexture(texJugador);


    // Cerramos la ventana y liberamos recursos
    CloseWindow();

    return 0;
}

