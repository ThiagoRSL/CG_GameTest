#include "ContainerElement.h"

ContainerElement::ContainerElement(float vx[], float vy[], int vertexes, int margin_top, int margin_left, float* background_color, float* border_color, float spaceBetween, int direction, int orientation)
 :Element(vx, vy, vertexes, 0, 0, background_color, border_color)
{
    this->spacing = spacing;
    this->direction = direction;
    this->orientation = orientation;
    this->alignment = 0;
}
void ContainerElement::AddChild(Element* elem)
{
    ChildrenElement.push_back(elem);
    this->AdjustChildrenPosition();
}
void ContainerElement::AdjustChildrenPosition()
{
    int i;
    int childrenNumber = ChildrenElement.size();
    float totalChildrenWidth = (childrenNumber+1)*spaceBetween;
    float totalChildrenHeight = (childrenNumber+1)*spaceBetween;
    float remainingContainerWidth = this->width - totalChildrenWidth;
    float remainingContainerHeight = this->width - totalChildrenHeight;
    for(Element* child : ChildrenElement)
    {
        totalChildrenWidth += child.GetWidth();
        totalChildrenHeight += child.GetHeight();
    }

    switch(direction)
    {
        case 0: //Horizontal
            if(totalChildrenWidth <= this->GetWidth())
            {
                float x, y;
                x = this->MarginLeft + remainingContainerWidth;
                y = this->MarginTop + remainingContainerHeight;

                for(i = 0; i < childrenNumber; i++)
                {
                    ChildrenElement.at(i)->UpdateMargin(x,y)
                }
            }
            else printf("Elementos maiores que o container.");
            break;
        default
            printf("Direção não existe.");
            break;
    }

    if()
}
