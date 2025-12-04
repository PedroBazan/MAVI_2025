#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif
#include <string>
#include "raylib.h"
#include "PlataformaNube.h"
#include "RectanguloMovimiento.h"
#include "Piso.h"
#include "PersonajePrincipal.h"
#include "Enemigo.h"

using namespace std;

int main(void)
{
    // Inicializamos una ventana de hd píxeles con un título personalizado
    InitWindow(1280, 720, "Trabajo de MAVI Integrador");

    // agrego sonido
    InitAudioDevice();

    // Configuramos el framerate deseado (opcional, pero recomendado)
    SetTargetFPS(60);

    Color fondo = { 0, 255, 0, 1 };//color violeta personalizado
    Color texto = DARKPURPLE;  // color de texto personalizado
   
    //Cargo el fondo de una imagen
    Texture2D fondoImagen = LoadTexture("FondoJuego.png");
    Texture2D texturaNube = LoadTexture("Nube.png");
    Texture2D texJugador = LoadTexture("Cthulhito.png");
    Texture2D texTesoro = LoadTexture("tesorito.png");
    Texture2D texEnemigo = LoadTexture("Enemigo.png");
    Sound sonidoSalto = LoadSound("boing.wav");
    SetTextureFilter(fondoImagen, TEXTURE_FILTER_BILINEAR);

    // Crear piso
    Rectangle piso = { 0, 650, 1280, 70 };
    Piso pisoVisual(0, 650, 1280, 70, GREEN);
    
    // Crear personaje
    PersonajePrincipal jugador(&texJugador, { 200, 200 });

    // nube voladora
    RectanguloMovimiento rect(&texturaNube, { 200, 200 }, { 200, 150 }, 120, 60);

    //enemigo
    Enemigo enemigo(&texEnemigo, 
        500, 300,      // posición inicial
        60, 60,        // ancho - alto
        150.0f,        // velocidad vertical
        200.0f,        // límite arriba
        600.0f         // límite abajo
    );
   

    //nubes quietas (hice un array para simplificar)
    PlataformaNube plataformas[] = {
    PlataformaNube(&texturaNube, 200, 500, 120, 40, WHITE),
    //PlataformaNube(&texturaNube, 400, 400, 120, 40, WHITE), //desactivada para darle dificultad pero lo activo para probar ganar
    PlataformaNube(&texturaNube, 800, 500, 120, 40, WHITE),
    PlataformaNube(&texturaNube, 650, 220, 120, 40, WHITE),
    PlataformaNube(&texturaNube, 1040, 220, 120, 40, WHITE)
    };
    int cantPlataformas = sizeof(plataformas) / sizeof(plataformas[0]);

    // Tesoro encima de la 4ta nube (indice 3)
    float escalaTesoro = 1.0f; 
    float anchoTesoro = texTesoro.width * escalaTesoro;
    float altoTesoro = texTesoro.height * escalaTesoro;

    Rectangle tesoroRect = {
        plataformas[3].rect.x + plataformas[3].rect.width / 2 - anchoTesoro / 2,
        plataformas[3].rect.y - altoTesoro - 1, // un poquito arriba
        anchoTesoro,
        altoTesoro
    };

    //condicion de gameover
    bool perdiste = false;

    //condicion de victoria
    bool ganaste = false;

    // boton para reiniciar 
    Rectangle botonReiniciar = {
        1280 / 2.0f - 100,   // x
        720 / 2.0f + 80,    // y
        200,                 // ancho
        50                   // alto
    };

    

    // Bucle principal del juego (se repite hasta que se cierre la ventana)
    while (!WindowShouldClose())
    {
        // Agrego letra P para cerrar el programa
        if (IsKeyPressed(KEY_P)) {
            CloseWindow();
                break;
        }  
        if (IsKeyPressed(KEY_R)) {
            perdiste = false;
            ganaste = false;   // tecla para reiniciar

            jugador.reiniciar({ 200, 200 });
            rect.reiniciar({ 200, 200 }, { 350, 180 });
        }
        
        float dt = GetFrameTime();  // obligatorio para movimiento

        if (!perdiste && !ganaste) {
            // Actualizo nube en movimiento y jugador SOLO si no perdiste
            rect.actualizar(dt, plataformas, cantPlataformas);
            enemigo.actualizar(dt);

            jugador.actualizar(
                dt,
                piso,
                plataformas,
                cantPlataformas,
                rect.getRect(), 
                sonidoSalto
                );


            // si el jugador toca el piso  GAME OVER
            Rectangle rectJugador = jugador.getRect();
            float bottomJugador = rectJugador.y + rectJugador.height;

            if (bottomJugador >= piso.y) {
                perdiste = true;
            }
			// si el jugador toca el enemigo GAME OVER
            if (CheckCollisionRecs(jugador.getRect(), enemigo.getRect())) {
                perdiste = true;
            }

            // si el jugador toca el tesoro  GANASTE
            if (CheckCollisionRecs(rectJugador, tesoroRect)) {
                ganaste = true;
            }
        }
        if (perdiste || ganaste) {
            Vector2 mouse = GetMousePosition();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointRec(mouse, botonReiniciar))
            {
                // Reiniciar estados
                perdiste = false;
                ganaste = false;

                // volver a posiciones originales
                jugador.reiniciar({ 200, 200 });
                rect.reiniciar({ 200, 200 }, { 350, 180 });
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
        enemigo.dibujar();// dibujo el enemigo

        // dibujo nubes estaticas en array
        for (int i = 0; i < cantPlataformas; i++)
            plataformas[i].dibujar();

        // dibujo tesoro
        if (!ganaste) {
            DrawTexturePro(
                texTesoro,
                { 0, 0, (float)texTesoro.width, (float)texTesoro.height }, 
                tesoroRect,                                                
                { 0, 0 },                                                  
                0.0f,                                                      
                WHITE
            );
        }



		// Dibujamos textos informativos en pantalla
        DrawText(TextFormat("Resolucion: %dx%d", GetScreenWidth(), GetScreenHeight()), 10, 10, 20, BLACK);
        DrawText("mover-> D, mover <- A, Espacio salta, P para salir, R reiniciar ", 250, 10, 20, BLACK);
        DrawText("El piso es lava! El tesoro gana! ", 10, 70, 20, BLACK);
        DrawText(TextFormat("Jugador X: %.1f Y: %.1f", jugador.getRect().x, jugador.getRect().y), 10, 40, 20, BLACK);
        // mensaje de game over
        if (perdiste || ganaste) {
            const char* mensaje = perdiste ? "PERDISTE!" : "GANASTE!";
            int fontSize = 60;
            int textWidth = MeasureText(mensaje, fontSize);
            int x = GetScreenWidth() / 2 - textWidth / 2;
            int y = GetScreenHeight() / 2 - fontSize / 2;
            DrawText(mensaje, x, y, fontSize, perdiste ? RED : GREEN);

            // Boton reiniciar
            Vector2 mouse = GetMousePosition();
            bool hover = CheckCollisionPointRec(mouse, botonReiniciar);

            DrawRectangleRec(botonReiniciar, hover ? DARKGRAY : GRAY);

            const char* txtBoton = "REINICIAR";
            int fontSizeBoton = 20;
            int textWidthBoton = MeasureText(txtBoton, fontSizeBoton);
            int bx = botonReiniciar.x + botonReiniciar.width / 2 - textWidthBoton / 2;
            int by = botonReiniciar.y + botonReiniciar.height / 2 - fontSizeBoton / 2;

            DrawText(txtBoton, bx, by, fontSizeBoton, BLACK);
        }

        // Finalizamos el dibujo
        EndDrawing();
    }
	// descargo la textura de la imagen
    UnloadTexture(fondoImagen);
    UnloadTexture(texturaNube);
    UnloadTexture(texJugador);
    UnloadTexture(texTesoro);
    UnloadTexture(texEnemigo);
    CloseAudioDevice();


    // Cerramos la ventana y liberamos recursos
    CloseWindow();

    return 0;
}

