#include "SliderElement.h"

SliderElement::SliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color)
    :Element(vx, vy, vertexes, background_color, border_color)
{
    this->label_side = 1;
    this->label = nullptr;
    this->sliding = false;
    this->val = 0;
    this->barHeight = 20;
    this->barWidth = 6;

    this->bar_y0 = this->UpperMostY() + (height/2) - (barHeight/2);
    this->bar_y1 = bar_y0 + barHeight;

    this->bar_x0 = this->LeftMostX();
    this->bar_x1 = bar_x0 + barWidth;

    this->val = ((this->bar_x0 - this->LeftMostX())/width);
    ((this->bar_x0 - this->LeftMostX())/width);
}

SliderElement::SliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, char* label, int label_length)
    :Element(vx, vy, vertexes, background_color, border_color)
{
    this->label_side = 1;
    this->sliding = false;
    this->val = 0;
    this->barHeight = 20;
    this->barWidth = 6;

    this->bar_y0 = this->UpperMostY() + (height/2) - (barHeight/2);
    this->bar_y1 = bar_y0 + barHeight;

    this->bar_x0 = this->LeftMostX();
    this->bar_x1 = bar_x0 + barWidth;

    this->val = ((this->bar_x0 - this->LeftMostX())/width);
    this->label = new char(label_length);

    int i;
    for(i = 0; i < label_length; i++)
    {
        this->label[i] = label[i];
    }
}

SliderElement::SliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, char* label, int label_length, int label_side)
    :Element(vx, vy, vertexes, background_color, border_color)
{
    this->label_side = label_side;
    this->sliding = false;
    this->val = 0;
    this->barHeight = 20;
    this->barWidth = 6;

    this->bar_y0 = this->UpperMostY() + (height/2) - (barHeight/2);
    this->bar_y1 = bar_y0 + barHeight;

    this->bar_x0 = this->LeftMostX();
    this->bar_x1 = bar_x0 + barWidth;

    this->val = ((this->bar_x0 - this->LeftMostX())/width);
    this->label = new char(label_length);

    int i;
    printf("%s", label);
    for(i = 0; i < label_length; i++)
    {
        this->label[i] = label[i];
    }
}
void SliderElement::Render()
{
    UpdateBarPosition();
    CreateBody();
    RenderSlidingBar();
    if(label != nullptr) RenderLabel();
}

void SliderElement::UpdateBarPosition()
{
    //printf("Value %f", this->val);
    this->bar_x0 = (this->val*width) + this->LeftMostX();
    this->bar_x1 = bar_x0 + barWidth;
}
void SliderElement::RenderSlidingBar()
{
    if(sliding)
    {
        int mouse_x = MouseManager::shared_instance().PosX;
        int mouse_y = MouseManager::shared_instance().PosY;
        float left_corner_x = this->LeftMostX();
        float right_corner_x = left_corner_x + width;

        if(mouse_x >= left_corner_x && mouse_x <= right_corner_x) this->bar_x0 = mouse_x;
        else if(mouse_x < left_corner_x) this->bar_x0 = left_corner_x;
        else if(mouse_x > right_corner_x) this->bar_x0 = right_corner_x;

        this->bar_x1 = bar_x0 + barWidth;
        this->val = ((this->bar_x0 - this->LeftMostX())/width);
    }
    float x0, x1, y0, y1;
    x0 = bar_x0 - barWidth/2;
    x1 = bar_x1 - barWidth/2;
    y0 = bar_y0;
    y1 = bar_y1;

    CV::color(0.8,0,0,1);
    CV::rectFill(x0, y0, x1, y1);
}
void SliderElement::RenderLabel()
{
    CV::color(1,1,1,1);
    switch(label_side)
    {
        case -1:
            CV::text(vertexesX[0] - 140, vertexesY[0] + (vertexesY[2] - vertexesY[0]), this->label);
            break;
        case 1:
            CV::text(vertexesX[1] + 10, vertexesY[0] + (vertexesY[2] - vertexesY[0]), this->label);
            break;
        case 3:
            CV::text(vertexesX[0] + 75, vertexesY[0] - (vertexesY[2] - vertexesY[0]), this->label);
            break;
        default:
            CV::text(vertexesX[1] + 10, vertexesY[0] + (vertexesY[2] - vertexesY[0]), this->label);
            break;
    }
}

int SliderElement::MouseInteraction(int button, int state)
{
    if(button == 0)
    {
        if(state == 0)
        {
            this->StartDragSlideBar();
            return 2;
        }
        else if(state == 1)
        {
            this->StopDragSlideBar();
        }
    }
    return 0;
}

bool SliderElement::Colide(int x, int y)
{
    int c = 0;
    float x0, x1, y0, y1;

    y0 = this->bar_y0;
    y1 = this->bar_y1;
    x0 = this->bar_x0 - barWidth/2;
    x1 = this->bar_x1 - barWidth/2;

    if(GeometryAux::Intercept(8000, 8000, x, y, x0, y0, x1, y0)) c += 1;
    if(GeometryAux::Intercept(8000, 8000, x, y, x1, y0, x1, y1)) c += 1;
    if(GeometryAux::Intercept(8000, 8000, x, y, x1, y1, x0, y1)) c += 1;
    if(GeometryAux::Intercept(8000, 8000, x, y, x0, y1, x0, y0)) c += 1;

    if(c%2 == 1) return true;
    return Element::Colide(x, y);
}

void SliderElement::StartDragSlideBar()
{
    sliding = true;
}
void SliderElement::StopDragSlideBar()
{
    sliding = false;
}



float SliderElement::GetValue()
{
    return this->val;
}
