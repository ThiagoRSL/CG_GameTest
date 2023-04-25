#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "MouseManager.h"
#include "gl_canvas2d.h"
#include "GeometryAux.h"
#include <array>

class Element
{
    public:
        //Element(float vx[], float vy[], int vertexes, int margin_top, int margin_left, bool* configs, float* background_color, float* border_color);
        Element(float vx[], float vy[], int vertexes, float* background_color, float* border_color);
        void MoveElement(int delta_x, int delta_y);
        virtual int MouseInteraction(int button, int state);
        virtual bool Colide(int x, int y);
        void DrawCollisionBoxesDebug();

        bool IsInsideBox(float x0,float y0,float x1,float y1);
        void SetInteractable(bool val);
        bool IsInteractable();

        float LeftMostX();
        float UpperMostY();
        float GetWidth();
        float GetHeight();
        float* GetBackgroundColorReference(){return this->background_color;}
        float* GetBorderColorReference(){return this->border_color;}
        float* GetSelectedScaleReference(){return this->scale;}

        virtual void Render();
    protected:
        float scale[1];
        int vertexes;
        int margin_top;
        int margin_left;
        float background_color[4];
        float border_color[4];

        float* vertexesX;
        float* vertexesY;

        virtual void CreateBody();
        virtual void CreateBorder();

        float width;
        float height;
    private:
        bool interactable;
};

#endif // ELEMENT_H
