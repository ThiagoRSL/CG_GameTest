#include "RenderManager.h"

RenderManager::RenderManager()
{

}

void RenderManager::RenderAll()
{
    int i;
    for (i = 0; i < renderList.size(); i++)
    {
        renderList.at(i)->Render();
    }
}

void RenderManager::SetFirstPosition(Renderable* element)
{
    int i;
    for (i = 0; i < renderList.size(); i++)
    {
        if(renderList.at(i) == element)
        {
            renderList.erase(renderList.begin()+i);
            renderList.push_back(element);
        }
    }
}

void RenderManager::AddRenderableToList(Renderable* element)
{
    renderList.push_back(element);
}


/*bool RenderManager::VerifyMouseInteraction(int x, int y, int button, int state)
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
}*/
