#include "FigureManager.h"

FigureManager::FigureManager()
{
    //RenderManager::renderList = std::list<Renderizable*>;
    this->StandardBackgroundColor[0] = 0.5;
    this->StandardBackgroundColor[1] = 0.5;
    this->StandardBackgroundColor[2] = 0.5;
    this->StandardBorderColor[0] = 0.75;
    this->StandardBorderColor[1] = 0.75;
    this->StandardBorderColor[2] = 0.75;

    this->placingFigure = nullptr;
    this->vx = nullptr;
    this->vy = nullptr;
    this->vn = 0;

    //this->draw_vx;
    //draw_vy.push_back(y);
    this->draw_vn = 0;

    this->isPlacingFigure = false;
}
void FigureManager::RenderAll()
{
    int i;
    for (i = 0; i < this->figuresRenderList.size(); i++)
    {
        this->figuresRenderList.at(i)->Render();
    }
    if(this->selectedFigure != nullptr) this->RenderEditMode();
    if(this->drawMode) this->RenderDrawMode();
    if(this->drawSelectionBox) this->DrawSelection();
}

void FigureManager::RenderDebug()
{
    int i;
    for (i = 0; i < figuresRenderList.size(); i++)
    {
        figuresRenderList.at(i)->DrawCollisionBoxesDebug();
    }
}

void FigureManager::RenderEditMode()
{
    int i, j;
    float x0, y0, x1, y1;
    Point coordinates;

    if(!this->selectedFigure->IsShapeLocked())
    {
        CV::color(0,150,0,90);
        for (i = 0; i < this->vn; i++)
        {
            CV::circle(this->vx[i], this->vy[i], FigureManager::VertexInteractAreaSize, 20);
        }
    }
}

void FigureManager::RenderDrawMode()
{
    float x = MouseManager::shared_instance().PosX;
    float y = MouseManager::shared_instance().PosY;

    CV::color(1,1,1,0.5);
    CV::circle(x, y, FigureManager::VertexInteractAreaSize, 20);

    int i;
    if(draw_vn > 2)
    {
        float vx[draw_vn+2], vy[draw_vn+2];
        for(i = 0; i < draw_vn; i++)
        {
            vx[i] = draw_vx.at(i);
            vy[i] = draw_vy.at(i);
        }
        vx[draw_vn] = x;
        vy[draw_vn] = y;
        vx[draw_vn+1] = draw_vx.at(0);
        vy[draw_vn+1] = draw_vy.at(0);
        Figure* newFigure = new Figure(vx, vy, draw_vn, StandardBackgroundColor, StandardBorderColor);
        newFigure->Select();
        newFigure->Render();
    }
}

Figure* FigureManager::CreateFigure(float vx[], float vy[], int vertexes,float* background_color, float* border_color)
{
    Figure* newFigure = new Figure(vx, vy, vertexes, background_color, border_color);
    figuresRenderList.push_back(newFigure);
    return newFigure;
}
std::string* FigureManager::GetFiguresAsString()
{
    int figures_number = this->CountFigures();
    std::string* figuresAsString = new std::string[figures_number];
    int i;
    for(i = 0; i < figures_number; i++)
    {
        Figure* fg = this->figuresRenderList.at(i);
        figuresAsString[i] = fg->GetFigureAsString();
    }
    return figuresAsString;
}
int FigureManager::CountFigures()
{
    return figuresRenderList.size();
}
void FigureManager::CreateTriangle()
{
    float centerX = MouseManager::shared_instance().PosX;
    float centerY = MouseManager::shared_instance().PosY;

    float vx[3] = {centerX, centerX+15, centerX-15};
    float vy[3] = {centerY+15, centerY-15,centerY-15};
    int vn = 3;
    float* background_color = this->StandardBackgroundColor;
    float* border_color = this->StandardBorderColor;
    Figure* newFigure = this->CreateFigure(vx, vy, vn, background_color, border_color);

    SetFirstPosition(newFigure);
    SetSelectedFigure(newFigure);
    SetDraggingFigure(newFigure);
}

void FigureManager::CreateSquare()
{
    float centerX = MouseManager::shared_instance().PosX;
    float centerY = MouseManager::shared_instance().PosY;

    float vx[4] = {centerX+15, centerX+15, centerX-15, centerX-15};
    float vy[4] = {centerY+15, centerY-15,centerY-15, centerY+15};
    int vn = 4;
    float* background_color = this->StandardBackgroundColor;
    float* border_color = this->StandardBorderColor;
    Figure* newFigure = this->CreateFigure(vx, vy, vn, background_color, border_color);

    SetFirstPosition(newFigure);
    SetSelectedFigure(newFigure);
    SetDraggingFigure(newFigure);
}

void FigureManager::CreateLosangle()
{
    float centerX = MouseManager::shared_instance().PosX;
    float centerY = MouseManager::shared_instance().PosY;

    float vx[4] = {centerX, centerX+15, centerX, centerX-15};
    float vy[4] = {centerY+30, centerY,centerY-30, centerY};
    int vn = 4;
    float* background_color = this->StandardBackgroundColor;
    float* border_color = this->StandardBorderColor;
    Figure* newFigure = this->CreateFigure(vx, vy, vn,  background_color, border_color);

    SetFirstPosition(newFigure);
    SetSelectedFigure(newFigure);
    SetDraggingFigure(newFigure);
}

/*void FigureManager::CreatePentagon()
{
    float centerX = MouseManager::shared_instance().PosX;
    float centerY = MouseManager::shared_instance().PosY;

    float vx[4] = {centerX, centerX+15, centerX, centerX-15};
    float vy[4] = {centerY+30, centerY,centerY-30, centerY};
    int vn = 4;
    int margin_top = 0;
    int margin_left = 0;
    float* background_color = this->StandardBackgroundColor;
    float* border_color = this->StandardBorderColor;
    Figure* newFigure = this->CreateFigure(vx, vy, vn, margin_top, margin_left, background_color, border_color);
}*/

void FigureManager::DrawingStart()
{
    drawMode = true;
}

void FigureManager::AddDrawPoint(float x, float y)
{
    draw_vx.push_back(x);
    draw_vy.push_back(y);
    draw_vn += 1;
}

void FigureManager::DrawingEnd()
{
    drawMode = false;
    int i;
    float vx[draw_vn+1], vy[draw_vn+1];
    for(i = 0; i < draw_vn; i++)
    {
        vx[i] = draw_vx.at(i);
        vy[i] = draw_vy.at(i);
    }
    vx[draw_vn] = draw_vx.at(0);
    vy[draw_vn] = draw_vy.at(0);
    Figure* newFigure = this->CreateFigure(vx, vy, draw_vn, this->StandardBackgroundColor, this->StandardBorderColor);

    draw_vx.clear();
    draw_vy.clear();
    draw_vn = 0;
}


void FigureManager::SetFirstPosition(Figure* figure)
{
    int i;
    for (i = 0; i < figuresRenderList.size(); i++)
    {
        if(figuresRenderList.at(i) == figure)
        {
            figuresRenderList.erase(figuresRenderList.begin()+i);
            figuresRenderList.push_back(figure);
            return;
        }
    }
}

//Selection Box
void FigureManager::DrawSelection()
{
    CV::color(0,0.4,0.4,0.4);
    CV::rect(this->selectedBoxXo, this->selectedBoxYo, MouseManager::shared_instance().PosX, MouseManager::shared_instance().PosY);
    CV::color(0,0.4,0.4,0.2);
    CV::rectFill(this->selectedBoxXo, this->selectedBoxYo, MouseManager::shared_instance().PosX, MouseManager::shared_instance().PosY);
}
void FigureManager::StartSelectionBox()
{
    this->selectedBoxXo = MouseManager::shared_instance().PosX;
    this->selectedBoxYo = MouseManager::shared_instance().PosY;
    this->drawSelectionBox = true;
}
void FigureManager::StopSelectionBox()
{
    float x1 = MouseManager::shared_instance().PosX;
    float y1 = MouseManager::shared_instance().PosY;
    this->SelectElementsInBox(this->selectedBoxXo, this->selectedBoxYo, x1, y1);

    this->drawSelectionBox = false;
    this->selectedBoxXo = 0;
    this->selectedBoxYo = 0;
}

void FigureManager::SelectElementsInBox(float x0, float y0, float x1, float y1)
{
    for(Figure* fig : figuresRenderList)
    {
        if(fig->IsInsideBox(x0, y0, x1, y1))
        {
            fig->Select();
            selectedFigures.push_back(fig);
        }
    }
}
void FigureManager::SetSelectedFigure(Figure* figure)
{
    this->UnsetSelectedFigure();
    this->selectedFigure = figure;
    this->vx = this->selectedFigure->GetVertexesX();
    this->vy = this->selectedFigure->GetVertexesY();
    this->vn = this->selectedFigure->GetVertexesNumber();
    this->selectedFigure->Select();
    this->selected_figure_callback_function();
}
void FigureManager::SetDraggingFigure(Figure* figure)
{
    this->UnsetDraggingFigure();
    this->draggingFigure = figure;
    this->draggingFigure->Drag();
}
void FigureManager::SetDraggingFigureVertex(Figure* figure, int index_vertex)
{
    this->UnsetDraggingFigure();
    this->draggingFigure = figure;
    this->draggingFigure->DragVertex(index_vertex);
}
void FigureManager::SetDraggingFigureVertexes(Figure* figure, int* index_vertex, int number)
{
    this->UnsetDraggingFigure();
    this->draggingFigure = figure;
    this->draggingFigure->DragVertexes(index_vertex, number);
}

void FigureManager::UnsetSelectedFigure()
{
    int numberSelectedFigures = selectedFigures.size();
    if(numberSelectedFigures > 1)
    {
        int i;
        for(i = 0; i < numberSelectedFigures; i++)
        {
            selectedFigures.at(i)->Unselect();
        }
    }
    selectedFigures.clear();
    if(this->selectedFigure != nullptr) this->selectedFigure->Unselect();
    this->selectedFigure = nullptr;
    this->unselected_figure_callback_function();
}
void FigureManager::UnsetDraggingFigure()
{
    if(this->draggingFigure != nullptr) this->draggingFigure->Undrag();
    this->draggingFigure = nullptr;
}
void FigureManager::DeleteSelectedFigure()
{
    if(this->selectedFigure != nullptr)
    {
        UnsetDraggingFigure();
        DeleteFigure(this->selectedFigure);
        this->selectedFigure = nullptr;
    }
}
void FigureManager::DeleteFigure(Figure* figure)
{
    int i;
    for(i = 0; i < figuresRenderList.size(); i++)
    {
        if(figure == figuresRenderList.at(i))
        {
            figuresRenderList.erase(figuresRenderList.begin()+i);
            delete figure;
            return;
        }
    }
}
void FigureManager::DeleteAllFigures()
{
    int i;
    Figure* fig;
    UnsetDraggingFigure();
    UnsetSelectedFigure();
    for(i = figuresRenderList.size()-1; i >= 0; i--)
    {
        fig = figuresRenderList.at(i);
        figuresRenderList.erase(figuresRenderList.begin()+i);
        delete fig;
    }
}
int FigureManager::CheckEditVertexInteraction(float x, float y)
{
    int i;
    for(i = 0; i < this->vn; i++)
    {
        printf("NÓ %i", i);
        float distanceBetween = GeometryAux::DistanceBetween(x, y, this->vx[i], this->vy[i]);
        if(distanceBetween < this->VertexInteractAreaSize)
        {
            printf("\n ACHEIIIIIIIIIIII %i", i);
            printf("\n ESTA PORA É X: %f e Y: %f \n O MOUSE É %f e %f \n A DISTANCIA ENTRE ELES É: %f", vx[i], vy[i], x, y, distanceBetween);
            return i;
        }
    }
    return -1;
}
void FigureManager::VerifyKeyboardInteraction(int key)
{
    switch(key)
    {
        case 127:
            for(Figure* fig : selectedFigures)
            {
                printf("A");
                if(selectedFigure == fig) continue;
                DeleteFigure(fig);
            }
            this->DeleteSelectedFigure();
            break;
    }
}
void FigureManager::VerifyMouseInteraction(int x, int y, int button, int state)
{
    if(drawMode)
    {
        if(button == 0 && state == 1) AddDrawPoint(x, y);
        if(button == 2 && state == 1) DrawingEnd();
        return;
    }
    if(IsDraggingFigure())
    {
        if(button == 0 && state == 1)
        {
            UnsetDraggingFigure();
            return;
        }
    }
    //Desclicou
    if(button == 0 && state == 1)
    {
        if(this->drawSelectionBox)
        {
            this->StopSelectionBox();
            return;
        }
    }

    //Selected figure interactions
    if(this->selectedFigure != nullptr)
    {
        if(button == 0 && state == 0)
        {
            int index_clicked_vertex = this->CheckEditVertexInteraction(x, y);
            if(index_clicked_vertex >= 0 && !this->selectedFigure->IsShapeLocked())
            {
                this->UnsetDraggingFigure();
                this->SetDraggingFigureVertex(this->selectedFigure, index_clicked_vertex);
                return;
            }
        }
    }

    bool colideSomething = false;
    int i;
    for (i = figuresRenderList.size()-1; i >= 0; i = i-1)
    {
        Figure* figure = figuresRenderList.at(i);
        if(figure->Colide(x, y))
        {
            colideSomething = true;
            switch(button)
            {
                case(-2):
                    glutSetCursor(5);
                    changedCursor = true;
                    break;
                case(0):
                    if(state == 0)
                    {
                        SetFirstPosition(figure);
                        SetSelectedFigure(figure);
                        SetDraggingFigure(figure);
                    }
                    else if(state == 1)
                    {
                        //SetSelectedFigure();
                        //SetDraggingFigure();
                    }
                    break;
                case(1):
                    break;
                case(2):
                    printf("BOTAO DIREITO");
                    break;
                default:
                    printf("UNRECOGNIZED MOUSE BUTTON PRESSED");
                    break;
            }
            if(button == 0 && state == 0) break;
        }
    }
    if(!colideSomething && button == 0 && state == 0)
    {
        this->UnsetSelectedFigure();
        this->StartSelectionBox();
        this->clickOut = true;
    }
    if(!colideSomething && button == 0 && state == 1 && !this->clickOut)
    {
        this->UnsetSelectedFigure();
        this->clickOut = false;
    }
    if(!colideSomething && changedCursor)
    {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        changedCursor = false;
    }
}

bool FigureManager::IsDraggingFigure()
{
    if(draggingFigure != nullptr)
        return true;
    return false;
}
void FigureManager::Rotate(float degrees)
{
    if(this->selectedFigure != nullptr)
        this->selectedFigure->Rotate(degrees);
}
void FigureManager::Resize(float size_diff)
{
    if(this->selectedFigure != nullptr)
        this->selectedFigure->Resize(size_diff);
}


float* FigureManager::GetSelectedBackgroundColorReference()
{
    return this->selectedFigure->GetBackgroundColorReference();

}
float* FigureManager::GetSelectedBorderColorReference()
{
    return this->selectedFigure->GetBorderColorReference();
}
float* FigureManager::GetSelectedScaleReference()
{
    return this->selectedFigure->GetSelectedScaleReference();
}
bool FigureManager::HasSelectedFigure()
{
    if(selectedFigure != nullptr)
        return true;
    return false;
}
