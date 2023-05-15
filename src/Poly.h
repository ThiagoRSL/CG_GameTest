#ifndef POLY_H
#define POLY_H

#include <stdio.h>
#include <vector>
#include "Vec2.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "GeometryAux.h"

class Poly : public Renderable
{
    public:
        Poly();
        Poly(float x, float y);
        Poly(float x, float y, float RGB[3]);

        void SetAnchor(float x, float y);
        void SetOrientation(float x, float y);
        void AddVertex(Vec2* vertex);
        void AddVertex(float x, float y);
        void Resize(float scalar);
        void Rotate(float degrees);
        void Transform(float matrix[2][2]);
        void Move(float speed);
        bool HasCollision(float x, float y);


        void Render();
    protected:
        float background_color[4];
        float border_color[4];

        Pnt2* anchor;
        Vec2 orientationVector;
        std::vector<Vec2*> Vertexes;

        void RenderBody();
        void RenderBorder();
        void RenderVertexes();
    private:

};

#endif // POLYGON_H
