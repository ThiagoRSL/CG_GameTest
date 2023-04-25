#include "Figure.h"

Figure::Figure(float vx[], float vy[], int vertexes, float* background_color, float* border_color)
    :Element(vx, vy, vertexes, background_color, border_color)
{
    this->vertexesDragging = new bool[vertexes]();
    this->vertexesXAtDrag = new float[vertexes]();
    this->vertexesYAtDrag = new float[vertexes]();
    this->dragging = false;
    this->selected = false;
    this->shapeLocked = false;
    this->draggedAtX = 0;
    this->draggedAtY = 0;
    this->draggedWhereX = 0;
    this->draggedWhereY = 0;
    this->centerX = 0;
    this->centerY = 0;

    this->showCenter = true;
    this->showFigure = true;
    this->UpdateCenterPoint();
}

void Figure::Render()
{
    if(this->dragging) this->UpdateDragPosition();
    if(this->showFigure)
    {
        this->CreateBody();
        this->CreateBorder();
    }
    if(this->selected)
    {
        this->CreateSelectedBorder();
        if(this->showCenter) this->RenderCenterPoint();
    }
}

void Figure::RenderCenterPoint()
{
    CV::color(5);
    CV::circleFill(this->centerX, this->centerY, 5, 30);
}

void Figure::DragVertex(int index_vertex)
{
    if(this->shapeLocked) return;

    this->Undrag();
    this->draggedAtX = MouseManager::shared_instance().PosX;
    this->draggedAtY = MouseManager::shared_instance().PosY;

    this->vertexesXAtDrag[index_vertex] = this->vertexesX[index_vertex];
    this->vertexesYAtDrag[index_vertex] = this->vertexesY[index_vertex];
    this->vertexesDragging[index_vertex] = true;

    dragging = true;
}
void Figure::DragVertexes(int* indexes_vertex, int number)
{
    if(this->shapeLocked) return;

    this->Undrag();
    this->draggedAtX = MouseManager::shared_instance().PosX;
    this->draggedAtY = MouseManager::shared_instance().PosY;

    int i;
    for(i = 0; i < number; i++)
    {
        this->vertexesXAtDrag[indexes_vertex[i]] = this->vertexesX[indexes_vertex[i]];
        this->vertexesYAtDrag[indexes_vertex[i]] = this->vertexesY[indexes_vertex[i]];
        this->vertexesDragging[indexes_vertex[i]] = true;
    }

    dragging = true;
}
bool Figure::Colide(int x, int y)
{
    int i, a, b;
    int counter = 0, counter2 = 0;
    for(i = 0; i < this->vertexes; i++)
    {
        a = i;
        if(i+1 >= this->vertexes) b = 0;
        else b = i+1;
        if(GeometryAux::Intercept(8000, 8000, x, y, this->centerX, this->centerY, this->vertexesX[a], this->vertexesY[a]))
        {
            counter += 1;
        }
        if(GeometryAux::Intercept(8000, 8000, x, y, this->centerX, this->centerY, this->vertexesX[b], this->vertexesY[b]))
        {
            counter += 1;
        }
        if(GeometryAux::Intercept(8000, 8000, x, y, this->vertexesX[a], this->vertexesY[a], this->vertexesX[b], this->vertexesY[b]))
        {
            counter += 1;
        }
        if(counter%2 == 1) return true;
    }
    return false;
}

//void MouseInteraction(int button, int state);

void Figure::CreateBody()
{
    CV::color(background_color[0], background_color[1], background_color[2], background_color[3]);
    float vx[this->vertexes+2], vy[this->vertexes+2];

    //Definindo o ponto inicial como o ponto central da figura, assim ele pertencerá ao conjunto de vertices de todos os triangulos que compõe o poligono.
    vx[0] = this->centerX;
    vy[0] = this->centerY;

    //Adicionando os demais pontos
    int i, a, b, c;
    for (i = 1; i < this->vertexes+1;i++)
    {
        vx[i] = this->vertexesX[i-1];
        vy[i] = this->vertexesY[i-1];
    }

    //Adicionando o primeiro ponto novamente para ele fechar a figura.
    vx[this->vertexes+1] = this->vertexesX[0];
    vy[this->vertexes+1] = this->vertexesY[0];
    CV::polygonFill(vx, vy, this->vertexes+2);
}
void Figure::CreateSelectedBorder()
{
    int i, j;
    //Desenha a borda da figura.
    CV::color(0,0,150,255);
    /*float vx[vertexes];
    float vy[vertexes];

    for(i = 0; i < this->vertexes; i++)
    {

    }*/

    CV::polygon(this->vertexesX, this->vertexesY, this->vertexes);

    //Desenha os circulos nos vértices da figura.


    //Desenha os quadrados nas arestas da figura.
    float x0, y0, x1, y1;
    Point coordinates;

}

void Figure::Drag()
{
    this->draggedAtX = MouseManager::shared_instance().PosX;
    this->draggedAtY = MouseManager::shared_instance().PosY;

    int i;
    for (i = 0; i < this->vertexes;i++)
    {
        this->vertexesXAtDrag[i] = this->vertexesX[i];
        this->vertexesYAtDrag[i] = this->vertexesY[i];
        this->vertexesDragging[i] = true;
    }
    dragging = true;
}
void Figure::Undrag()
{
    int i;
    for (i = 0; i < this->vertexes;i++)
    {
        this->vertexesDragging[i] = false;
    }
    dragging = false;
}

void Figure::Select()
{
    if(selected == false)
    {
        selected = true;
    }
}
void Figure::Unselect()
{
    selected = false;
}

void Figure::UpdateDragPosition()
{
    float dragDeltaX = draggedWhereX - (draggedAtX - MouseManager::shared_instance().PosX);
    float dragDeltaY = draggedWhereY - (draggedAtY - MouseManager::shared_instance().PosY);

    int i;
    for (i = 0; i < this->vertexes;i++)
    {
        if(vertexesDragging[i] == true)
        {
            this->vertexesX[i] = this->vertexesXAtDrag[i] + dragDeltaX;
            this->vertexesY[i] = this->vertexesYAtDrag[i] + dragDeltaY;
        }
    }

    this->UpdateCenterPoint();
}
void Figure::UpdateCenterPoint()
{
    int i = 0;
    float x = 0.0, y = 0.0;
    for(i = 0; i < this->vertexes; i++)
    {
        x = x + this->vertexesX[i];
        y = y + this->vertexesY[i];
    }
    this->centerX = x / this->vertexes;
    this->centerY = y / this->vertexes;
}

void Figure::SetShapeLocked(bool shapeLocked)
{
    this->shapeLocked=shapeLocked;
}
bool Figure::IsShapeLocked()
{
    return this->shapeLocked;
}
float* Figure::GetVertexesX()
{
    return this->vertexesX;
}
float* Figure::GetVertexesY()
{
    return this->vertexesY;
}
int Figure::GetVertexesNumber()
{
    return this->vertexes;
}
void Figure::Resize(float size_diff)
{
    int i;
    float offsetX = centerX;
    float offsetY = centerY;
    for(i = 0; i < this->vertexes; i++)
    {
        //Calculando coordenadas relativas ao centro.
        float virtual_x = ( this->vertexesX[i] - offsetX ) * (1 + size_diff);
        float virtual_y = ( this->vertexesY[i] - offsetY ) * (1 + size_diff);

        this->vertexesX[i] = virtual_x + offsetX;
        this->vertexesY[i] = virtual_y + offsetY;
    }
}
int Figure::Rotate(float degrees)
{
    int i;
    float rotate_vx;
    float rotate_vy;

    float offsetX = centerX;
    float offsetY = centerY;
    for(i = 0; i < this->vertexes; i++)
    {
        //Calculando coordenadas relativas ao centro.
        float virtual_x = this->vertexesX[i] - offsetX;
        float virtual_y = this->vertexesY[i] - offsetY;

        //Aplicando Matrix de Rotação
        rotate_vx = (virtual_x * cosf(degrees)) - (virtual_y * sinf(degrees));
        rotate_vy = (virtual_x * sinf(degrees)) + (virtual_y * cosf(degrees));

        this->vertexesX[i] = rotate_vx + offsetX;
        this->vertexesY[i] = rotate_vy + offsetY;
    }

}
std::string Figure::GetFigureAsString()
{
    std::string strFg = "";
    strFg = strFg + (std::to_string(this->vertexes)) + " [";
    int i;
    for(i = 0; i < this->vertexes; i++)
    {
        strFg = strFg + "(" + (std::to_string( (int) this->vertexesX[i])) + ", " + (std::to_string( (int) this->vertexesY[i])) + ")";
        if(i != this->vertexes-1) strFg = strFg + ", ";
    }
    strFg = strFg + "]";
    /*strFg = strFg + " [(" + (std::to_string( (int) (this->background_color[0] * 255) )) + ", "
    + (std::to_string( (int) (this->background_color[1] * 255) )) + ", "
    + (std::to_string( (int) (this->background_color[2] * 255) )) + ")]";

    strFg = strFg + " [(" + (std::to_string( (int) (this->border_color[0] * 255) )) + ", "
    + (std::to_string( (int) (this->border_color[1] * 255) )) + ", "
    + (std::to_string( (int) (this->border_color[2] * 255) )) + ")]";*/
    return strFg;
}
