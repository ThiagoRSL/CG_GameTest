#include "Poly.h"

Poly::Poly()
{
    this->orientationVector = Vec2();
}

Poly::Poly(float x, float y)
{
    this->anchor = new Pnt2(x, y);
    this->orientationVector = Vec2(0, 1);
    this->orientationVector.SetAnchor(this->anchor);
}

void Poly::Move(float speed)
{
    Vec2 moveVec = (orientationVector * speed);
    this->anchor->ApplyVec2(moveVec);
}

void Poly::SetAnchor(float x, float y)
{
    this->anchor->x = x;
    this->anchor->y = y;
}

void Poly::AddVertex(Vec2* vertex)
{
    vertex->SetAnchor(this->anchor);
    this->Vertexes.push_back(vertex);
}

void Poly::AddVertex(float x, float y)
{
    Vec2* vertex = new Vec2(x, y);
    vertex->SetAnchor(this->anchor);
    this->Vertexes.push_back(vertex);
}

void Poly::Resize(float scalar)
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->Mult(scalar);
    }
}

void Poly::Rotate(float degrees)
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->RotateDegrees(degrees);
    }
    orientationVector.RotateDegrees(degrees);
}

void Poly::Render()
{
    //this->RenderVertex();
    this->RenderBody();
    //this->RenderBorder();
}

void Poly::RenderBody()
{
    CV::color(255, 0, 0);
    int i, a;
    for(i = 0; i < Vertexes.size(); i++)
    {
        if(i != Vertexes.size()-1)
            a = i+1;
        else
            a = 0;

        float vx[3] = {anchor->x, anchor->x - Vertexes.at(i)->x, anchor->x - Vertexes.at(a)->x};
        float vy[3] = {anchor->y, anchor->y - Vertexes.at(i)->y, anchor->y - Vertexes.at(a)->y};
        CV::polygonFill(vx, vy, 3);
    }
}


void Poly::RenderBorder()
{

}

void Poly::RenderVertexes()
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->Render();
    }
}
