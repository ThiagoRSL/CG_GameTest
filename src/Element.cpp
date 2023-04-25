#include "Element.h"
#include "RenderManager.h"

Element::Element(float *vx, float *vy, int vertexes, float* background_color, float* border_color)
{
    this->vertexesX = new float[vertexes]();
    this->vertexesY = new float[vertexes]();
    this->vertexes = vertexes;
    this->margin_top = margin_top;
    this->margin_left = margin_left;
    this->interactable = true;
    this->scale[0] = 1;

    this->background_color[3] = 1;
    this->border_color[3] = 1;

    int i;
    for (i = 0; i < vertexes; i++)
    {
        this->vertexesX[i] = vx[i];
        this->vertexesY[i] = vy[i];
    }
    for (i = 0; i < 3; i++)
    {
        Element::background_color[i] = background_color[i];
        Element::border_color[i] = border_color[i];
    }

    //Encontra vertice mais distante do primeiro.
    //APENAS VÁLIDO PARA ELEMENTOS RETANGULARES.
    int index = 0;
    for (i = 0; i < vertexes; i++)
    {
        if(GeometryAux::DistanceBetween(vx[0], vy[0], vx[i], vy[i]) > GeometryAux::DistanceBetween(vx[0], vy[0], vx[index], vy[index]))
        {
            index = i;
        }
    }
    height = vy[0] - vy[index];
    width = vx[0] - vx[index];
    if(height < 0) height = height * (-1);
    if(width < 0) width = width * (-1);
}
void Element::SetInteractable(bool val)
{
    this->interactable = val;
}
bool Element::IsInteractable()
{
    return this->interactable;
}
void Element::Render()
{
    CreateBody();
    CreateBorder();
}

int Element::MouseInteraction(int button, int state)
{
    // 0 = Nada aconteceu.
    // 1 = Interação comum, pode prosseguir.
    // 2 = Interação privilegiada, exige resposta.
    switch(button)
    {
        case(-2):
            printf("\tMouse over Element.");
            break;
        case(0):
            break;
        case(1):
            break;
        case(2):
            printf("BOTAO DIREITO");
            break;
        default:
            printf("UNRECOGNIZED MOUSE BUTTON PRESSED");
            break;
    }
    return 0;
}
bool Element::Colide(int x, int y)
{
    int i, a, b, c;
    c = 0;
    for(i = 0; i < this->vertexes; i++)
    {
        a = i;
        if(i+1 >= this->vertexes) b = 0;
        else b = i+1;
        if(GeometryAux::Intercept(8000, 8000, x, y, this->vertexesX[a], this->vertexesY[a], this->vertexesX[b], this->vertexesY[b]))
        {
            c += 1;
        }
    }
    if(c%2 == 1) return true;
    return false;
}
void Element::MoveElement(int delta_x, int delta_y)
{
    Element::margin_top += delta_x;
    Element::margin_left += delta_y;
}
void Element::CreateBody()
{
    CV::color(background_color[0], background_color[1], background_color[2], background_color[3]);
    CV::polygonFill(this->vertexesX, this->vertexesY, this->vertexes);
}
void Element::CreateBorder()
{
    CV::color(border_color[0], border_color[1], border_color[2], border_color[3]);
    CV::polygon(this->vertexesX, this->vertexesY, this->vertexes);
}

bool Element::IsInsideBox(float x0,float y0,float x1,float y1)
{
    float xa = x0, ya = y0, xb = x1, yb = y1;
    if(x0 > x1)
    {
        xa = x1;
        xb = x0;
    }
    if(y0 > y1)
    {
        ya = y1;
        yb = y0;
    }


    int i;
    for(i = 0; i < this->vertexes; i++)
    {
        float x = this->vertexesX[i];
        float y = this->vertexesY[i];
        if(x >= xa && x <= xb && y >= ya && y <= yb)
        {
            return true;
        }
    }
    return false;
}

void Element::DrawCollisionBoxesDebug()
{
    int i, a,b;
    for(i = 0; i < this->vertexes; i++)
    {
        if(i+1 >= this->vertexes) a = i+1 - this->vertexes;
        else a = i+1;
        if(i+2 >= this->vertexes) b = i+2 - this->vertexes;
        else b = i+2;

        float vx[] = {this->vertexesX[i], this->vertexesX[a], this->vertexesX[b]};
        float vy[] = {this->vertexesY[i], this->vertexesY[a], this->vertexesY[b]};
        CV::color(i);
        CV::polygon(vx,vy,3);
    }
}

float Element::LeftMostX()
{
    int index_smallest = 0;
    int i;
    for(i = 0; i < vertexes; i++)
    {
        if (this->vertexesX[i] < this->vertexesX[index_smallest]) index_smallest = i;
    }

    return this->vertexesX[index_smallest];
}

float Element::UpperMostY()
{
    int index_smallest = 0;
    int i;
    for(i = 0; i < vertexes; i++)
    {
        if (vertexesY[i] < vertexesY[index_smallest]) index_smallest = i;
    }

    return vertexesY[index_smallest];
}


/*static float getXFromLine(float y, float x0, float y0, float x1, float y1)
{
    float m = (y0-y1)/(x0-x1);
    float x = x1 - ((y1-y)/m)
    return x;
}
static float getYFromLine(float x, float x0, float y0, float x1, float y1)
{
    float m = (y0-y1)/(x0-x1);
    float y = (m * (x-x1)) + y1
    return y;
}*/

