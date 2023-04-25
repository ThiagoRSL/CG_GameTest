#include "RenderManager.h"

RenderManager::RenderManager()
{
    this->lastInteracted = nullptr;
}

void RenderManager::RenderAll()
{
    int i;
    for (i = 0; i < elementsRenderList.size(); i++)
    {
        elementsRenderList.at(i)->Render();
    }
}
Element* RenderManager::CreateElement(float vx[], float vy[], int vertexes, float* background_color, float* border_color)
{
    Element* newElement = new Element(vx, vy, vertexes, background_color, border_color);
    elementsRenderList.push_back(newElement);
    return newElement;
}
Element* RenderManager::CreateElement(float vx[], float vy[], int vertexes, float* background_color, float* border_color, bool interactable)
{
    Element* newElement = new Element(vx, vy, vertexes,background_color, border_color);
    newElement->SetInteractable(interactable);
    elementsRenderList.push_back(newElement);
    return newElement;
}
ButtonElement* RenderManager::CreateButtonElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, void (*callback_function)())
{
    ButtonElement* newElement = new ButtonElement(vx, vy, vertexes, background_color, border_color, callback_function);
    elementsRenderList.push_back(newElement);
    return newElement;
}
SliderElement* RenderManager::CreateSliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color)
{
    SliderElement* newElement = new SliderElement(vx, vy, vertexes, background_color, border_color);
    elementsRenderList.push_back(newElement);
    return newElement;
}
SliderElement* RenderManager::CreateSliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, char* label, int label_length)
{
    SliderElement* newElement = new SliderElement(vx, vy, vertexes, background_color, border_color, label, label_length);
    elementsRenderList.push_back(newElement);
    return newElement;
}
SliderElement* RenderManager::CreateSliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, char* label, int label_length, int label_side)
{
    SliderElement* newElement = new SliderElement(vx, vy, vertexes, background_color, border_color, label, label_length, label_side);
    elementsRenderList.push_back(newElement);
    return newElement;
}
void RenderManager::SetFirstPosition(Element* element)
{
    int i;
    for (i = 0; i < elementsRenderList.size(); i++)
    {
        if(elementsRenderList.at(i) == element)
        {
            elementsRenderList.erase(elementsRenderList.begin()+i);
            elementsRenderList.push_back(element);
        }
    }
}
bool RenderManager::VerifyMouseInteraction(int x, int y, int button, int state)
{
    if(lastInteracted != nullptr && button == 0 && state == 1)
    {
       lastInteracted->MouseInteraction(button, state);
       lastInteracted = nullptr;
       return true;
    }
    bool collideSomething = false;
    int i;
    for (i = elementsRenderList.size()-1; i >= 0; i = i-1)
    {
        Element* element = elementsRenderList.at(i);
        if(element->Colide(MouseManager::shared_instance().PosX, MouseManager::shared_instance().PosY))
        {
            if(element->IsInteractable())
            {
               collideSomething = true;
                if(button == -2 && state == -2)
                {
                    glutSetCursor(GLUT_CURSOR_CYCLE);
                    changedCursor = true;
                }
                printf("B1");
                if(element->MouseInteraction(button, state) == 2) lastInteracted = element;
                printf("B2");
            }
            if(button == 0 && (state == 0 || state == 1)) return true;
        }
    }
    if(!collideSomething && changedCursor) glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    return false;
}
