#pragma once
#include "Input.h"

#include <glut.h>
#include <memory>

#include "Scene.h"
#include "GraphicObject.h"

extern std::unique_ptr<Scene> scene;

glm::vec2* Input::MouseClick(int button, int state, int x, int y)
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  if (button == GLUT_LEFT_BUTTON)
    {
	  if (state == GLUT_DOWN) {
        /* Ein Knopf wurde gedrückt. Passenden Callback festlegen */
			if (button == GLUT_LEFT_BUTTON){
				if (scene->getGraphicObjectMode() == GraphicObject::Mode::SELECTION)
					return scene->selectGraphicObjectAt(x, scene->getFrameHeight() - y - 17);

				else{
					GraphicObject* go = scene->getCurrentGraphicObject();
					if (go != NULL) {
						go->addPoint(x, scene->getFrameHeight() - y - 17);
						go->calcPivot();
						scene->add(go);
					}
					return NULL;
				}
				//glutPostRedisplay();
			}
			//glutPostRedisplay();
			//else if (button == GLUT_RIGHT_BUTTON)
				//glutMotionFunc (rightClick);*/
      }
      //g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
		
    }

}

void Input::MouseMotion(glm::vec2* v, int x, int y){
	int click_distance = 5;
	int real_y = scene->getFrameHeight() - y - 17;

	//if (g_bButton1Down)
		if (v != NULL && scene->getGraphicObjectMode() == GraphicObject::Mode::SELECTION){
			v->x = x;
			v->y = real_y;
		}
}

void Input::KeyboardPressed(unsigned char key, int x, int y) {
	switch(key){
	case 's':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::SELECTION); break;	
	case 'l':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::LINE); break;	
	case 'e':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::BEZIER); break;
	case 'b':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::BSPLINE); break;
	case 'c':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::CIRCLE); break;
	case 't':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::TRIANGLE); break;
	case 'r':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::RECTANGLE); break;
	case 'p':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::POLYGON); break;
	case 'y':
		scene->setCurrentGraphicObjectMode(GraphicObject::Mode::PYTHAGORAS); break;
	case 127: // del/entf
		scene->clearGraphicObjects(); break;
	case 27: // ESC
		exit(1); break;

	case 8:{ // backspace
		for (auto& go : scene->getAllGraphicObjects())
			go->setTransformationMatrix(Transform());
		break;
	}

	default:
		break;
	}
}

void Input::KeyboardSpecialPressed(int key, int x, int y) {

	Transform::Mode transMode = scene->getGraphicTransformMode();

	switch(key){
	case GLUT_KEY_LEFT:{ // left
		if (transMode == Transform::Mode::TRANSLATE)
			scene->setInputTransform(Transform(Transform::translate(-10, 0)));
		else if (transMode == Transform::Mode::ROTATE)
			scene->setInputTransform(Transform(Transform::rotate(1, 0)));
		else if (transMode == Transform::Mode::SCALE)
			scene->setInputTransform(Transform(Transform::scale(1.2, 1)));
		break;
	}
	case GLUT_KEY_RIGHT:{ // right
		if (transMode == Transform::Mode::TRANSLATE)
			scene->setInputTransform(Transform(Transform::translate(10, 0)));
		else if (transMode == Transform::Mode::ROTATE)
			scene->setInputTransform(Transform(Transform::rotate(-1, 0)));
		else if (transMode == Transform::Mode::SCALE)
			scene->setInputTransform(Transform(Transform::scale(0.8, 1)));
		break;
	}
	case GLUT_KEY_UP:{ // up
		if (transMode == Transform::Mode::TRANSLATE)
			scene->setInputTransform(Transform(Transform::translate(0, 10)));
		else if (transMode == Transform::Mode::ROTATE)
			scene->setInputTransform(Transform(Transform::rotate(1, 0)));
		else if (transMode == Transform::Mode::SCALE)
			scene->setInputTransform(Transform(Transform::scale(1, 1.2)));
		break;
	}
	case GLUT_KEY_DOWN:{ // down
		if (transMode == Transform::Mode::TRANSLATE)
			scene->setInputTransform(Transform(Transform::translate(0, -10)));
		else if (transMode == Transform::Mode::ROTATE)
			scene->setInputTransform(Transform(Transform::rotate(-1, 0)));
		else if (transMode == Transform::Mode::SCALE)
			scene->setInputTransform(Transform(Transform::scale(1, 0.8)));
		break;
	}

	

	case GLUT_KEY_F1:
		scene->setGraphicTransformtMode(Transform::Mode::TRANSLATE); break;
	case GLUT_KEY_F2:
		scene->setGraphicTransformtMode(Transform::Mode::ROTATE); break;	
	case GLUT_KEY_F3:
		scene->setGraphicTransformtMode(Transform::Mode::SCALE); break;	
	case GLUT_KEY_F4:
		scene->toggleShowVertices(); break;
	case GLUT_KEY_F5:
		scene->toggleAutoRotation(); break;	
	case GLUT_KEY_F6:
		for (GraphicObject* go : scene->getAllGraphicObjects())
			go->calcPivot();
		scene->toggleLocalGlobalRotation(); break;	

	default:
		break;
	}
}