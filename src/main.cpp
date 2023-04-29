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
#include "FPSManager.h"
#include "Character.h"

Character* player_character;

bool moving;
int rotating;

bool control_rotating_right;
bool control_rotating_left;
bool control_moving;

void render()
{
    CV::clear(0,0,0);
    FPSManager::shared_instance().UpdateFrames();
    RenderManager::shared_instance().RenderAll();
    if(moving)
        player_character->Move(500/FPSManager::shared_instance().GetFrames());
    if(rotating != 0)
        player_character->Rotate(rotating*200/FPSManager::shared_instance().GetFrames());
}


void keyboard(int key)
{
    printf("\nTecla: %d" , key);

    switch(key)
    {
      //seta para a esquerda
      case 99:
        //tecla C
      case 120:
        //tecla X
      case 122:
        //tecla Z
        player_character->Shoot();
      break;
      case 200:
        if(!control_rotating_left)
        {
            rotating = -1;
        }
      break;
      case 201:
        if(!control_moving)
        {
            control_moving = true;
            moving = true;
        }
      break;
      case 202:
        if(!control_rotating_right)
        {
            rotating = 1;
        }
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
        control_rotating_left = false;
        control_rotating_right = false;
        rotating = 0;
	  break;
      case 201:
        control_moving = false;
        moving = false;
	  break;
	  case 202:
        control_rotating_right = false;
        control_rotating_left = false;
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
        player_character->SetAnchor(x, y);
    }
}

int main(void)
{
    control_rotating_right = false;
    control_rotating_left = false;
    control_moving = false;

   //Sleep(1000);
    player_character = new Character(400, 400);
    player_character->AddVertex(-20,-25);
    player_character->AddVertex(-10,-40);
    player_character->AddVertex(10,-40);
    player_character->AddVertex(20,-25);
    player_character->AddVertex(20,25);
    player_character->AddVertex(-20,25);

    RenderManager::shared_instance().AddRenderableToList(player_character);

    int screenWidth = 1080;
    int screenHeight = 720;
    CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
    CV::run();
}
