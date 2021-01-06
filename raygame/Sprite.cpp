#include <Matrix3.h>
#include <Vector2.h>
#include "Sprite.h"
#include "raylib.h"
#include <cmath>

Sprite::Sprite(Texture2D* texture)
{
    m_texture = texture;
}

Sprite::Sprite(const char* path)
{
    m_texture = new RAYLIB_H::Texture2D();
    *m_texture = RAYLIB_H::LoadTexture(path);
}

void Sprite::draw(MathLibrary::Matrix3 transform)
{
    //Finds the scale of the sprite
    float xMagnitude = (float)round(MathLibrary::Vector2(transform.m11, transform.m21).getMagnitude());
    float yMagnitude = (float)round(MathLibrary::Vector2(transform.m12, transform.m22).getMagnitude());
    m_width = (int)xMagnitude;
    m_height = (int)yMagnitude;

    //Sets the sprite center to the transform origin
    MathLibrary::Vector2 pos = MathLibrary::Vector2(transform.m13, transform.m23);
    MathLibrary::Vector2 forward = MathLibrary::Vector2(transform.m11, transform.m21);
    MathLibrary::Vector2 up = MathLibrary::Vector2(transform.m12, transform.m22);
    pos = pos - (forward.getNormalized() * m_width / 2);
    pos = pos - (up.getNormalized() * m_height / 2);

    //Find the transform rotation in radians 
    float rotation = atan2(transform.m21, transform.m11);
    RAYLIB_H::Vector2 rayPos = { pos.x, pos.y };
    //Draw the sprite
    RAYLIB_H::DrawTextureEx(*m_texture, rayPos,
        (float)(rotation * 180.0f / PI), 32, WHITE);
}

