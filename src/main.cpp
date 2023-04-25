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
#include "FigureManager.h"
#include "Figure.h"
#include "Element.h"
#include "Vec2.h"
Vec2* v1;
Vec2* v2;
void render()
{
    CV::clear(0,0,0);
    v1->Render();
    v2->Render();
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
        v1->Rotate(-5.0);
        v2->Rotate(-5.0);
	  break;
      case 201:
        v1->Normalize();
	  break;
	  case 202:
        v1->Rotate(5.0);//FigureManager::shared_instance().Rotate(DEGREES_ROTATION);
        v2->Rotate(5.0);//FigureManager::shared_instance().Rotate(DEGREES_ROTATION);
	  break;
      case 203:
        *v2 = *v1 * 3.0f;
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
    v1 = new Vec2(100,100);
    v2 = new Vec2(300,100);

    int screenWidth = 1080;
    int screenHeight = 720;
    CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
    CV::run();
}
