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
Vec2* v1;
Vec2* v2;
void render()
{
    RenderManager::shared_instance().RenderAll();
}


void keyboard(int key)
{
   printf("\nTecla: %d" , key);
   if( key < 200 )
   {
      //opcao = key;
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
      case 50:
	     v1->Mult(0.5);
	  break;
      case 52:
	     v1->Sub(v2);
	  break;
      case 54:
	     v1->Sum(v2);
	  break;
      case 56:
	     v1->Mult(2);
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
        v1->RotateDegrees(-5.0);
        v2->RotateDegrees(-5.0);
	  break;
      case 201:
        v1->Normalize();
	  break;
	  case 202:
        v1->RotateDegrees(5.0);//FigureManager::shared_instance().Rotate(DEGREES_ROTATION);
        v2->RotateDegrees(5.0);//FigureManager::shared_instance().Rotate(DEGREES_ROTATION);
	  break;
      case 203:
        v1->Mult(2);
	  break;
   }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    MouseManager::shared_instance().PosX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    MouseManager::shared_instance().PosY = y;

    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);


}

int main(void)
{
    v1 = new Vec2(300,100);
    v2 = new Vec2(100,100);
    v1->SetAnchor(500,500);
    v2->SetAnchor(500,200);

    RenderManager::shared_instance().AddRenderableToList(v1);
    RenderManager::shared_instance().AddRenderableToList(v2);

    int screenWidth = 1080;
    int screenHeight = 720;
    CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
    CV::run();
}
