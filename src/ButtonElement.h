#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H

#include "Element.h"

class ButtonElement : public Element
{
    public:
        ButtonElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, void (*callback_function)());
        int MouseInteraction(int button, int state);
    protected:

    private:
        void (*callback_function)();
};

#endif // BUTTONELEMENT_H
