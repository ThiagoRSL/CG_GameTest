#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "Renderable.h"
#include "gl_canvas2d.h"

class Vec2 : public Renderable
{
    public:
        float x, y;

        Vec2();
        Vec2(float v[2]);
        Vec2(float x, float y);

        // Getters
        float GetNorm();

        // Sobrecarga de Operadores
        //inline vetor operator + ( const vetor v )
        inline Vec2 operator + (Vec2 v2);
        inline Vec2 operator - (Vec2 v2);
        inline Vec2 operator * (Vec2 v2);
        inline Vec2 operator * (float const& e);

        // Normaliza o proprio vetor
        void Normalize();
        // Rotaciona o vetor em alguns graus
        void Rotate(float degrees);

        void Render();

    protected:

    private:
};

#endif // VEC2_H
