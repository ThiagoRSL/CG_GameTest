#include "Vec2.h"

// Construtores
Vec2::Vec2()
{
    this->x = 0;
    this->y = 0;
}

Vec2::Vec2(float v[2])
{
    this->x = v[0];
    this->y = v[1];
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

// Getters e Setters
float Vec2::GetNorm()
{
    return sqrtf((x*x) + (y*y));
}

// Sobrecarga de operadores +, - e *
Vec2 Vec2::operator + ( Vec2 v2)
{
    return Vec2(this->x + v2.x, this->y + v2.y);
}
Vec2 Vec2::operator - ( Vec2 v2)
{
    return Vec2(this->x - v2.x, this->y - v2.y);
}
Vec2 Vec2::operator * ( Vec2 v2)
{
    return Vec2(this->x * v2.x, this->y * v2.y);
}
Vec2 Vec2::operator * (float const& e)
{
    return Vec2(this->x * e, this->y * e);
}


void Vec2::Normalize()
{
    float norm = this->GetNorm();
    this->x = this->x / norm;
    this->y = this->y / norm;
}

void Vec2::Rotate(float degrees)
{
    this->x = (this->x * cosf(degrees)) - (this->y * sinf(degrees));
    this->y = (this->x * sinf(degrees)) + (this->y * cosf(degrees));
}

void Vec2::Render()
{
    CV::color(1);
    CV::circle(0, 0, 10, 30);
    CV::color(2);
    CV::line(0, 0, this->x, this->y);
    CV::color(3);
    CV::circle(this->x, this->y, 10, 30);
}

