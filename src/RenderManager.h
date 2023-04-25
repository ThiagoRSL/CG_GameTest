#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "MouseManager.h"
#include "Element.h"
#include "ButtonElement.h"
#include "SliderElement.h"

typedef void (*callback_function)(void);

class RenderManager
{
    public:
        static RenderManager &shared_instance() {static RenderManager renderManager; return renderManager;}
        RenderManager();
        void RenderAll();
        Element* CreateElement(float vx[], float vy[], int vertexes, float* background_color, float* border_color);
        Element* CreateElement(float vx[], float vy[], int vertexes, float* background_color, float* border_color, bool interactable);
        ButtonElement* CreateButtonElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, void (*callback_function)());
        SliderElement* CreateSliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color);
        SliderElement* CreateSliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, char* label, int label_length);
        SliderElement* CreateSliderElement(float* vx, float* vy, int vertexes, float* background_color, float* border_color, char* label, int label_length, int label_side);
        void SetFirstPosition(Element* element);
        bool VerifyMouseInteraction(int x, int y, int button, int state);
        void SelectElement(Element* element);
        //AddToRenderQueue(Renderizable element, int priority_level);

        bool changedCursor;
    protected:

    private:
        Element* lastInteracted;
        Element* selectedElement;
        std::vector<Element*> elementsRenderList;


};

#endif // RENDERMANAGER_H

