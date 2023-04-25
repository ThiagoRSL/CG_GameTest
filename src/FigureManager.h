#ifndef FIGUREMANAGER_H
#define FIGUREMANAGER_H

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "Element.h"
#include "Figure.h"


class FigureManager
{
    public:
        static const int VertexInteractAreaSize = 10;
        float StandardBackgroundColor[3];
        float StandardBorderColor[3];
        static FigureManager &shared_instance() {static FigureManager figureManager; return figureManager;}
        FigureManager();
        std::string* GetFiguresAsString();;
        int CountFigures();


        void RenderAll();
        void RenderDebug();
        void RenderEditMode();
        void RenderDrawMode();

        Figure* CreateFigure(float vx[], float vy[], int vertexes, float* background_color, float* border_color);
        void CreateTriangle();
        void CreateSquare();
        void CreateLosangle();
        //void CreateCircle();

        void SetPlacingFigure(Figure* newFigure);
        void PlaceFigure();


        void SetFirstPosition(Figure* figure);

        void VerifyKeyboardInteraction(int key);
        void VerifyMouseInteraction(int x, int y, int button, int state);

        void DrawSelection();
        void StartSelectionBox();
        void StopSelectionBox();

        void DrawingStart();
        void AddDrawPoint(float x, float y);
        void DrawingEnd();

        void SelectElementsInBox(float x0, float y0, float x1, float y1);
        void SetSelectedFigure(Figure* figure);
        void SetDraggingFigure(Figure* figure);
        void SetDraggingFigureVertex(Figure* figure, int index_vertex);
        void SetDraggingFigureVertexes(Figure* figure, int* index_vertex, int number);
        void UnsetSelectedFigure();
        void UnsetDraggingFigure();
        void DeleteSelectedFigure();
        void DeleteFigure(Figure* figure);
        void DeleteAllFigures();
        void Rotate(float degrees);
        void Resize(float size_diff);

        int CheckEditVertexInteraction(float x, float y);
        bool IsDraggingFigure();

        float* GetSelectedBackgroundColorReference();
        float* GetSelectedBorderColorReference();
        float* GetSelectedScaleReference();
        bool HasSelectedFigure();
        void SetSelectionCallback( void (*callback_function)()) { this->selected_figure_callback_function = callback_function;}
        void SetUnselectionCallback( void (*callback_function)()) { this->unselected_figure_callback_function = callback_function;}
        //void SetSelectedFigureCallbackFunction(void (*selected_figure_callback_function)()) { this->selected_figure_callback_function = selected_figure_callback_function};

        //AddToRenderQueue(Renderizable element, int priority_level);
    protected:

    private:
        bool changedCursor;
        bool isMultipleSeleced;
        bool isPlacingFigure;
        bool clickOut;
        bool drawSelectionBox;
        float selectedBoxXo;
        float selectedBoxYo;

        Figure* selectedFigure;
        Figure* draggingFigure;
        Figure* placingFigure;
        std::vector<Figure*> figuresRenderList;
        std::vector<Figure*> selectedFigures;

        //Edit Mode
        float* vx;
        float* vy;
        int vn;
        void (*selected_figure_callback_function)();
        void (*unselected_figure_callback_function)();
        //Draw Mode
        bool drawMode;  //Define modo de desenho de forma livre.
        std::vector<float> draw_vx; //Define vetor de cordenadas x dos vertex da forma sendo desenhada.
        std::vector<float> draw_vy; //Define vetor de cordenadas y dos vertex da forma sendo desenhada.
        int draw_vn;    //Define numero de vertexes da forma sendo desenhada.

};

#endif // FIGUREMANAGER_H
