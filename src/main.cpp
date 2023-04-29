/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "gl_canvas2d.h"
#include "FileManager.h"
#include "MouseManager.h"
#include "RenderManager.h"
#include "Vec2.h"
#include "Poly.h"
Poly* poly;

bool moving;
int rotating;

void render()
{
    CV::clear(0,0,0);
    RenderManager::shared_instance().RenderAll();

    if(moving)
        poly->Move(1);
    if(rotating != 0)
        poly->Rotate(rotating);
}


void keyboard(int key)
{
    printf("\nTecla: %d" , key);

    switch(key)
    {
      //seta para a esquerda
      case 200:
        rotating = -1;
      break;
      case 201:
        moving = true;
      break;
      case 202:
        rotating = 1;
      break;
      case 203:
      break;
    }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    printf("\nLiberou: %d" , key);

   switch(key)
   {
      case 27:
	     //exit(0);
	  break;
	  //tecla "I"
      case 105:
	    // debugMode = !debugMode;
        break;
	  case 107:
        //ClearAllFigures();
        break;
	  case 108:
        //LoadSave();
        break;
	  case 109:
        //FileManager::shared_instance().SaveData(SavedFilePath, FigureManager::shared_instance().GetFiguresAsString(), FigureManager::shared_instance().CountFigures());
        break;
	  //seta para a esquerda
      case 200:
        rotating = 0;
	  break;
      case 201:
        moving = false;
	  break;
	  case 202:
        rotating = 0;
	  break;
      case 203:
	    //poly->Resize(2);
	  break;
   }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    MouseManager::shared_instance().PosX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    MouseManager::shared_instance().PosY = y;

    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

    if(button == 0 && state == 0)
    {
        poly->SetAnchor(x, y);
    }
}

int main(void)
{
   //Sleep(1000);
    poly = new Poly(400, 400);
    poly->AddVertex(-20,-25);
    poly->AddVertex(-10,-40);
    poly->AddVertex(10,-40);
    poly->AddVertex(20,-25);
    poly->AddVertex(20,25);
    poly->AddVertex(-20,25);

    RenderManager::shared_instance().AddRenderableToList(poly);

    int screenWidth = 1080;
    int screenHeight = 720;
    CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
    CV::run();
}
