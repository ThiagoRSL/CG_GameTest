#ifndef CONTAINERELEMENT_H
#define CONTAINERELEMENT_H

#include <stdlib.h>
#include <vector>
#include "Element.h"

class ContainerElement : public Element
{
    public:
        ContainerElement(float vx[], float vy[], int vertexes, int margin_top, int margin_left, float* background_color, float* border_color, int spaceBetween = 10, int direction = 0, int orientation = 0);
        void AddChild(Element* elem);
        void AdjustChildrenPosition();

    protected:

    private:
        int direction;   // 0 = Horizontal, 1 = Vertical
        int orientation; // 0 = Normal, 1 = Invertida
        int alignment;   // 0 = Centralizado
        int spacing; // 0 = igualmente distribuído
        std::vector<Element*> ChildrenElement;
};

#endif // CONTAINERELEMENT_H
