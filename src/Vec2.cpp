#include "Vec2.h"

// Construtores
Vec2::Vec2()
{
    this->x = 0;
    this->y = 0;
    this->anchor_x = 0;
    this->anchor_y = 0;
}

Vec2::Vec2(float v[2])
{
    this->x = v[0];
    this->y = v[1];
    this->anchor_x = 0;
    this->anchor_y = 0;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
    this->anchor_x = 0;
    this->anchor_y = 0;
}

// Setters
void Vec2::SetAnchor(float x, float y)
{
    this->anchor_x = x;
    this->anchor_y = y;
}

// Getters
float Vec2::GetNorm()
{
    return sqrtf((x*x) + (y*y));
}


// Sobrecarga de operadores +, - e *

inline Vec2 Vec2::operator + (const Vec2 v2) const
{
    return Vec2(this->x + v2.x, this->y + v2.y);
}
inline Vec2 Vec2::operator - (const Vec2 v2) const
{
    return Vec2(this->x - v2.x, this->y - v2.y);
}
inline Vec2 Vec2::operator * (const Vec2 v2) const
{
    return Vec2(this->x * v2.x, this->y * v2.y);
}

//Operações no próprio vetor
void Vec2::Mult(float scalar)
{
    this->x = this->x * scalar;
    this->y = this->y * scalar;
}

void Vec2::Sum(float scalar)
{
    this->x = this->x + scalar;
    this->y = this->y + scalar;
}

void Vec2::Sum(Vec2* v2)
{
    this->x = this->x + v2->x;
    this->y = this->y + v2->y;
}
void Vec2::Sub(Vec2* v2)
{
    this->x = this->x - v2->x;
    this->y = this->y - v2->y;
}

void Vec2::Normalize()
{
    float norm = this->GetNorm();
    this->x = this->x / norm;
    this->y = this->y / norm;
}

void Vec2::RotateDegrees(float degrees)
{
    this->RotateRadians(degrees * (PI / 180));
}

void Vec2::RotateRadians(float radians)
{
    float aux_x = this->x;
    float aux_y = this->y;
    this->x = (aux_x * cosf(radians)) - (aux_y * sinf(radians));
    this->y = (aux_x * sinf(radians)) + (aux_y * cosf(radians));
}

void Vec2::Render()
{
    CV::color(1);
    CV::circle(this->anchor_x, this->anchor_y, 10, 30);
    CV::color(2);
    CV::line(this->anchor_x, this->anchor_y, this->x + this->anchor_x, this->y + this->anchor_y);
    CV::color(3);
    CV::circle(this->x + this->anchor_x, this->y + this->anchor_y, 10, 30);
}

