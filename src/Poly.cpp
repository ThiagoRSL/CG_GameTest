#include "Poly.h"

Poly::Poly()
{
    this->anchor = new Pnt2(0, 0);
    this->orientationVector = Vec2();
    this->orientationVector.SetAnchor(this->anchor);
}

Poly::Poly(float x, float y)
{
    this->anchor = new Pnt2(x, y);
    this->orientationVector = Vec2(0, 1);
    this->orientationVector.SetAnchor(this->anchor);
}

Poly::Poly(float x, float y, float RGB[3])
{
    this->anchor = new Pnt2(x, y);
    this->orientationVector = Vec2(0, 1);
    this->orientationVector.SetAnchor(this->anchor);
    background_color[0] = RGB[0];
    background_color[1] = RGB[1];
    background_color[2] = RGB[2];
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
void Poly::SetOrientation(float x, float y)
{
    this->orientationVector.x = x;
    this->orientationVector.y = y;
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

void Poly::Transform(float matrix[2][2])
{
    int i;
    float x, y, newX, newY;
    for(i = 0; i < Vertexes.size(); i++)
    {
        x = Vertexes.at(i)->x;
        y = Vertexes.at(i)->y;
        newX = x * matrix[0][0] + y * matrix[0][1];
        newY = x * matrix[1][0] + y * matrix[1][1];
        Vertexes.at(i)->x = newX;
        Vertexes.at(i)->y = newY;
    }
}

void Poly::Render()
{
    //this->RenderVertex();
    this->RenderBody();
    //this->RenderBorder();
}

void Poly::RenderBody()
{
    CV::color(background_color[0], background_color[1], background_color[2]);
    int i, a;
    for(i = 0; i < Vertexes.size(); i++)
    {
        if(i != Vertexes.size()-1)
            a = i+1;
        else
            a = 0;

        float vx[3] = {anchor->x, anchor->x + Vertexes.at(i)->x, anchor->x + Vertexes.at(a)->x};
        float vy[3] = {anchor->y, anchor->y + Vertexes.at(i)->y, anchor->y + Vertexes.at(a)->y};
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

bool Poly::HasCollision(float x, float y)
{
    int i, a;
    for(i = 0; i < Vertexes.size(); i++)
    {
        if(i != Vertexes.size()-1)
            a = i+1;
        else
            a = 0;

        int counter = 0;
        if(GeometryAux::Intercept(8000, 8000, x, y, this->anchor->x, this->anchor->y, anchor->x + this->Vertexes.at(i)->x, anchor->y + this->Vertexes.at(i)->y))
        {
            counter += 1;
        }
        if(GeometryAux::Intercept(8000, 8000, x, y, this->anchor->x, this->anchor->y, anchor->x + this->Vertexes.at(a)->x, anchor->y + this->Vertexes.at(a)->y))
        {
            counter += 1;
        }
        if(GeometryAux::Intercept(8000, 8000, x, y, anchor->x + this->Vertexes.at(i)->x, anchor->y + this->Vertexes.at(i)->y, anchor->x + this->Vertexes.at(a)->x, anchor->y + this->Vertexes.at(a)->y))
        {
            counter += 1;
        }
        if(counter%2 == 1) return true;
    }

    return false;
}
