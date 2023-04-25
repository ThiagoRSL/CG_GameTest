#include "ButtonElement.h"

ButtonElement::ButtonElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, void (*callback_function)())
    :Element(vx, vy, vertexes, background_color, border_color)
{
    this->callback_function = callback_function;
}
int ButtonElement::MouseInteraction(int button, int state)
{
    printf("\nB1.1");
    if(button == 0 && state == 0)
    {
        printf("\nB1.2");
        this->callback_function();
        printf("\nB1.3");
        return 1;
    }
    return 0;
}
