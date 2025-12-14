#pragma once
#include "raylib.h"

class BolaRebote
{
public:
    BolaRebote(Vector2 startPos, float radius, float baseSpeed, int screenW, int screenH);

    void LoadSprite(const char* filename);
    void UnloadSprite();

    void Update(float dt, float speedMultiplier);
    void Draw() const;

private:
    Vector2 pos{};
    Vector2 vel{};
    float   r = 20.0f;
    float   speed = 200.0f;

    int screenWidth = 800;
    int screenHeight = 600;

    Texture2D sprite{};
    bool hasSprite = false;

    Vector2 RandomDirectionUnit() const;
    void BounceWithRandomDirection(bool hitVerticalWall, bool hitHorizontalWall);
};
