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
				
				//glutPostRedisplay();
			}
			//glutPostRedisplay();
			//else if (button == GLUT_RIGHT_BUTTON)
				//glutMotionFunc (rightClick);*/
      }
      //g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
		
    }
}


void Input::KeyboardPressed(unsigned char key, int x, int y) {
	switch(key){
	case 'l':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::LINE); break;	
	case 'b':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::BEZIER); break;
	case 'c':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::CIRCLE); break;
	case 't':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::TRIANGLE); break;
	case 'r':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::RECTANGLE); break;
	case 127: // del/entf
		scene->clearGraphicObjects(); break;
	case 27: // ESC
		exit(1); break;

	//37(left arrow)
	//38(up arrow)
	//39(right arrow)
	//40(down arrow)
	default:
		break;
	}
}

void Input::KeyboardSpecialPressed(int key, int x, int y) {
	switch(key){
	case GLUT_KEY_LEFT:{ // left
		//if (
		scene->setInputTransform(Transform(Transform::scale(-1,0)) * scene->getInputTransform());
		break;
	}
	case GLUT_KEY_RIGHT:{ // left
		//if (
		scene->setInputTransform(Transform(Transform::scale(1,0)) * scene->getInputTransform());
		break;
	}

	default:
		break;
	}
}