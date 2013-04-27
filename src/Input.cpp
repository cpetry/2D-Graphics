#pragma once
#include "Input.h"

#include <glut.h>
#include <memory>

#include "Scene.h"
#include "GraphicObject.h"

extern std::unique_ptr<Scene> scene;


void Input::leftClick(int x, int y){}
void Input::rightClick(int x, int y){}

void Input::MouseClick(int button, int state, int x, int y)
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  if (button == GLUT_LEFT_BUTTON)
    {
	  if (state == GLUT_DOWN) {
        /* Ein Knopf wurde gedrückt. Passenden Callback festlegen */
			if (button == GLUT_LEFT_BUTTON){
				GraphicObject* go = scene->getCurrentGraphicObject();
				go->addPoint(x, scene->getFrameHeight() - y - 17);
				scene->add(go);
			}
			//glutPostRedisplay();
			//else if (button == GLUT_RIGHT_BUTTON)
				//glutMotionFunc (rightClick);*/
      }
      //g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
		
    }
}
