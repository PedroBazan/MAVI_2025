#ifndef NDEBUG
#include <vld.h> 
#endif

#include "raylib.h"
#include "BolaRebote.h"

// Update bola
static void UpdateBall(BolaRebote& bola, float dt, float speedMultiplier)
{
    bola.Update(dt, speedMultiplier);
}

// Fondo escalado
static void DrawFondoEscalado(const Texture2D& fondo, int screenW, int screenH)
{
    DrawTexturePro(
        fondo,
        Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height },
        Rectangle{ 0, 0, (float)screenW, (float)screenH },
        Vector2{ 0, 0 },
        0.0f,
        WHITE
    );
}

// Dibujo
static void DrawGame(const Texture2D& fondo, const BolaRebote& bola, float speedMultiplier, int screenW, int screenH)
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFondoEscalado(fondo, screenW, screenH);
    bola.Draw();

    DrawText(TextFormat("Velocidad: x%.2f (Arriba/Abajo)", speedMultiplier), 10, 10, 20, RAYWHITE);

  
    EndDrawing();
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, " Bola Rebote");
    SetTargetFPS(60);

  

    
    Texture2D fondo = LoadTexture("assets/FondoJuego.png");
    TraceLog(LOG_INFO, "Fondo size: %d x %d (id=%d)", fondo.width, fondo.height, fondo.id);

    BolaRebote bola({ screenWidth * 0.5f, screenHeight * 0.5f }, 22.0f, 260.0f, screenWidth, screenHeight);
    bola.LoadSprite("assets/BolaRebote.png");

    float speedMultiplier = 1.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_UP)) speedMultiplier += 0.15f;
        if (IsKeyPressed(KEY_DOWN)) speedMultiplier -= 0.15f;

        if (speedMultiplier < 0.10f) speedMultiplier = 0.10f;
        if (speedMultiplier > 4.00f) speedMultiplier = 4.00f;

        UpdateBall(bola, dt, speedMultiplier);
        DrawGame(fondo, bola, speedMultiplier, screenWidth, screenHeight);
    }

    bola.UnloadSprite();
    UnloadTexture(fondo);
    CloseWindow();
    return 0;
}
