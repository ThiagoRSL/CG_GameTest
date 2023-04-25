#ifndef SLIDERELEMENT_H
#define SLIDERELEMENT_H

#include "Element.h"
#include "GeometryAux.h"


class SliderElement : public Element
{
    public:
        SliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color);
        SliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, char* label, int label_length);
        SliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, char* label, int label_length, int label_side);


        void UpdateBarPosition();
        void StartDragSlideBar();
        void StopDragSlideBar();
        int MouseInteraction(int button, int state);
        void DragSlideBar();
        bool Colide(int x, int y);


        float GetValue();
        float* GetValueReference(){ return &val;}
        void Render();
    protected:
        void RenderLabel();
        void RenderSlidingBar();

    private:
        bool sliding;
        float barHeight;
        float barWidth;

        float bar_x0;
        float bar_x1;
        float bar_y0;
        float bar_y1;

        float valueMax;
        float valueMin;
        float val;
        char* label;
        int label_side;
};

#endif // SLIDERELEMENT_H
