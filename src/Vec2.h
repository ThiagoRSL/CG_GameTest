#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "Renderable.h"
#include "gl_canvas2d.h"

class Vec2 : public Renderable
{
    public:
        float anchor_x, anchor_y;
        float x, y;

        Vec2();
        Vec2(float v[2]);
        Vec2(float x, float y);

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

        // Normaliza o proprio vetor
        void Normalize();
        // Rotaciona o vetor em alguns graus
        void Rotate(float degrees);

        void Render();

    protected:

    private:
};

#endif // VEC2_H
