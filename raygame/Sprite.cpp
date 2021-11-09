#include <Matrix3.h>
#include <Vector2.h>
#include "Sprite.h"
#include "raylib.h"
#include <cmath>

Sprite::~Sprite()
{
    RAYLIB_H::UnloadTexture(*m_texture);
    delete m_texture;
}

Sprite::Sprite(Texture2D* texture)
{
    m_texture = texture;
}

Sprite::Sprite(const char* path)
{
    m_texture = new Texture2D(RAYLIB_H::LoadTexture(path));
}

int Sprite::getWidth()
{
    return m_texture->width;
}

void Sprite::setWidth(int value)
{
    m_texture->width = value;
}

int Sprite::getHeight()
{
    return m_texture->height;
}

void Sprite::setHeight(int value)
{
    m_texture->height = value;
}

void Sprite::draw(MathLibrary::Matrix3 transform)
{
    //Finds the scale of the sprite
    float xMagnitude = (float)round(MathLibrary::Vector2(transform.m00, transform.m10).getMagnitude());
    float yMagnitude = (float)round(MathLibrary::Vector2(transform.m01, transform.m11).getMagnitude());
    setWidth((int)xMagnitude);
    setHeight((int)yMagnitude);

    //Sets the sprite center to the transform origin
    MathLibrary::Vector2 pos = MathLibrary::Vector2(transform.m02, transform.m12);
    MathLibrary::Vector2 forward = MathLibrary::Vector2(transform.m00, transform.m10);
    MathLibrary::Vector2 up = MathLibrary::Vector2(transform.m01, transform.m11);
    pos = pos - (forward.getNormalized() * getWidth() / 2);
    pos = pos - (up.getNormalized() * getHeight() / 2);

    //Find the transform rotation in radians 
    float rotation = atan2(transform.m21, transform.m11);
    RAYLIB_H::Vector2 rayPos = { pos.x, pos.y };

    //Draw the sprite
    RAYLIB_H::DrawTextureEx(*m_texture, rayPos,
        (float)(rotation * 180.0f / PI), 1, WHITE);
}

