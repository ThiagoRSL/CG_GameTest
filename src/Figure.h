#ifndef FIGURE_H
#define FIGURE_H

#include "Element.h"
#include "GeometryAux.h"

class Figure : public Element
{
    public:
        Figure(float vx[], float vy[], int vertexes, float* background_color, float* border_color);
        void Select();
        void Unselect();
        void Drag();
        void Undrag();
        void DragVertex(int index_vertex);
        void DragVertexes(int* indexes_vertex, int number);
        std::string GetFigureAsString();
        int Rotate(float degrees);
        void Resize(float size_diff);
        //void MouseInteraction(int button, int state);
        int CollideVertex(float x, float y);
        bool Colide(int x, int y);

        void SetShapeLocked(bool shapeLocked);
        bool IsShapeLocked();
        float* GetVertexesX();
        float* GetVertexesY();
        int GetVertexesNumber();


        void RenderCenterPoint();
        void Render();
    protected:
        void CreateBody();
        void CreateSelectedBorder();
        void UpdateDragPosition();
        void UpdateCenterPoint();

   private:
        float centerX;
        float centerY;

        int draggedAtX;
        int draggedAtY;
        int draggedWhereX;
        int draggedWhereY;

        float* vertexesXAtDrag;
        float* vertexesYAtDrag;
        bool* vertexesDragging;

        bool shapeLocked;
        bool draggable;
        bool selectable;
        bool dragging;
        bool selected;
        bool showCenter;
        bool showFigure;
};

#endif // FIGURE_H
