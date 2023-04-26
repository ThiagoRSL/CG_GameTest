#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "Renderable.h"
#include "gl_canvas2d.h"

#define PI 3.141992

class Vec2 : public Renderable
{
    public:
        float anchor_x, anchor_y;
        float x, y;

        Vec2();
        Vec2(float v[2]);
        Vec2(float x, float y);

        // Setters
        void SetAnchor(float x, float y);
        // Getters
        float GetNorm();

        // Sobrecarga de Operadores
        //inline vetor operator + ( const vetor v )
        inline Vec2 operator + (const Vec2 v2) const;
        inline Vec2 operator - (const Vec2 v2) const;
        inline Vec2 operator * (const Vec2 v2) const;
        inline Vec2 operator * (const float& e) const
        {
            return Vec2(this->x * e, this->y * e);
        }
        // Operações no próprio vetor
        void Mult(float scalar);
        void Sum(float scalar);
        void Sum(Vec2* v2);
        void Sub(Vec2* v2);

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
