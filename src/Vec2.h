#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "Renderable.h"
#include "gl_canvas2d.h"
#include "Pnt2.h"


class Vec2 : public Renderable
{
    public:
        Pnt2* anchor;
        float x, y;
        float RelativeX(){return this->anchor->x + x;}
        float RelativeY(){return this->anchor->y + y;}

        Vec2();
        Vec2(float v[2]);
        Vec2(float x, float y);

        // Setters
        void SetAnchor(Pnt2* point);
        // Getters
        float GetNorm();

        Vec2 operator* (const float& scalar)
        {
            Vec2 aux(x * scalar, y * scalar);
            return (aux);
        }
        Vec2 operator+ (const Vec2& vec)
        {
            Vec2 aux(x + vec.x, y + vec.y);
            return (aux);
        }
        // Opera��es no pr�prio vetor
        void Mult(float scalar);
        void Sum(float scalar);
        void Sum(Vec2* v2);
        void Sub(Vec2* v2);

        void ApplyAtPoint();
        // Normaliza o proprio vetor
        void Normalize();
        // Rotaciona o vetor em alguns graus
        void RotateDegrees(float degrees);
        void RotateRadians(float radians);

        void Render();

    protected:

    private:
};

#endif // VEC2_H
