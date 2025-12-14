#include "BolaRebote.h"
#include <cmath>

static Vector2 NormalizeSafe(Vector2 v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y);
    if (len <= 0.0001f) return { 1.0f, 0.0f };
    return { v.x / len, v.y / len };
}

BolaRebote::BolaRebote(Vector2 startPos, float radius, float baseSpeed, int screenW, int screenH)
{
    pos = startPos;
    r = radius;
    speed = baseSpeed;
    screenWidth = screenW;
    screenHeight = screenH;

    // dirección inicial aleatoria
    vel = RandomDirectionUnit();
}

void BolaRebote::LoadSprite(const char* filename)
{
    if (FileExists(filename))
    {
        sprite = LoadTexture(filename);
        hasSprite = true;
    }
    else
    {
        hasSprite = false;
    }
}

void BolaRebote::UnloadSprite()
{
    if (hasSprite)
    {
        UnloadTexture(sprite);
        hasSprite = false;
    }
}

Vector2 BolaRebote::RandomDirectionUnit() const
{
    float a = GetRandomValue(0, 359) * DEG2RAD;
    Vector2 v = { cosf(a), sinf(a) };
    return NormalizeSafe(v);
}

void BolaRebote::BounceWithRandomDirection(bool hitVerticalWall, bool hitHorizontalWall)
{
    Vector2 dir = RandomDirectionUnit();

    if (hitVerticalWall)
    {
        if (pos.x - r <= 0)          dir.x = fabsf(dir.x);
        if (pos.x + r >= screenWidth) dir.x = -fabsf(dir.x);
    }

    if (hitHorizontalWall)
    {
        if (pos.y - r <= 0)           dir.y = fabsf(dir.y);
        if (pos.y + r >= screenHeight) dir.y = -fabsf(dir.y);
    }

    vel = NormalizeSafe(dir);
}

void BolaRebote::Update(float dt, float speedMultiplier)
{
    // movimiento
    pos.x += vel.x * speed * speedMultiplier * dt;
    pos.y += vel.y * speed * speedMultiplier * dt;

    bool hitVertical = false;
    bool hitHorizontal = false;

    // bordes X
    if (pos.x - r <= 0)
    {
        pos.x = r;
        hitVertical = true;
    }
    else if (pos.x + r >= screenWidth)
    {
        pos.x = screenWidth - r;
        hitVertical = true;
    }

    // bordes Y
    if (pos.y - r <= 0)
    {
        pos.y = r;
        hitHorizontal = true;
    }
    else if (pos.y + r >= screenHeight)
    {
        pos.y = screenHeight - r;
        hitHorizontal = true;
    }

    // rebote con dirección aleatoria
    if (hitVertical || hitHorizontal)
    {
        BounceWithRandomDirection(hitVertical, hitHorizontal);
    }
}

void BolaRebote::Draw() const
{
    if (!hasSprite) return;

    Rectangle src = {
        0, 0,
        (float)sprite.width,
        (float)sprite.height
    };

    // El sprite ocupa EXACTAMENTE el diámetro del círculo lógico
    Rectangle dst = {
        pos.x,
        pos.y,
        r * 2.0f,
        r * 2.0f
    };

    // Origen centrado ? sprite alineado al círculo
    Vector2 origin = { r, r };

    DrawTexturePro(
        sprite,
        src,
        dst,
        origin,
        0.0f,
        WHITE
    );
}

