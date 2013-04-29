#define FREEGLUT_STATIC

#include <windows.h>		// Must have for Windows platform builds
#include <vector>
#include "gl/glew.h"
#include <glut.h>
#include <memory>
#include <string>
#include <sstream>


#include "Splines/Line.h"
#include "Primitives2D/Rectangle2D.h"
#include "Primitives2D/Triangle2D.h"
#include "Primitives2D/Polygon2D.h"
#include "Splines/Circle.h"
#include "Splines/BezierCurve.h"
#include "Splines/BSpline.h"
#include "Input.h"
#include "Scene.h"

int width = 1024, height = 768;
std::unique_ptr<Scene> scene(new Scene(width, height));
glm::vec2 mouse_position = glm::vec2(0,0);

void renderBitmapString(float x, float y, void *font,const char *string){
	const char *c;
    glRasterPos2f(x, y);
	for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3d(1.0, 0.0, 0.0);

	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0, glutGet( GLUT_WINDOW_WIDTH ), 0, glutGet( GLUT_WINDOW_HEIGHT ), -1, 1 );
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glRasterPos2f(0, 0);
	scene->drawAllGraphicObjects();
	glDrawPixels(scene->getFrameWidth(), scene->getFrameHeight(), GL_RGB, GL_UNSIGNED_BYTE, scene->getFrame());

    
	glLoadIdentity();
	int linestart = 50;
	int lineheight = 15;
	int linenum = 0;
		
	std::string mouse_pos;
	mouse_pos += "x: ";
	mouse_pos += std::to_string(static_cast<int>(mouse_position.x));
	mouse_pos += ", y: ";
	mouse_pos += std::to_string(static_cast<int>(mouse_position.y));

	if (mouse_position.x > 0)
		renderBitmapString(glutGet(GLUT_WINDOW_WIDTH)-150, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum * lineheight), GLUT_BITMAP_9_BY_15, mouse_pos.c_str());

	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "Commands: " );

	if (scene->getGraphicObjectMode() == GraphicObject::Mode::SELECTION) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "s = Selection" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicObjectMode() == GraphicObject::Mode::LINE) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "l = Line" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicObjectMode() == GraphicObject::Mode::CIRCLE) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "c = Circle" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicObjectMode() == GraphicObject::Mode::BEZIER) glColor3d(1.0, 1.0, 1.0); 
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "e = Bezier" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicObjectMode() == GraphicObject::Mode::BSPLINE) glColor3d(1.0, 1.0, 1.0); 
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "b = Bspline" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicObjectMode() == GraphicObject::Mode::RECTANGLE) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "r = Rectangle" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicObjectMode() == GraphicObject::Mode::TRIANGLE) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "t = Triangle" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicObjectMode() == GraphicObject::Mode::POLYGON) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "p = Polygon" );
		glColor3d(1.0, 0.0, 0.0);
	
	if (scene->getGraphicTransformMode() == Transform::Mode::TRANSLATE) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "F1 = Translation" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicTransformMode() == Transform::Mode::ROTATE) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "F2 = Rotation" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getGraphicTransformMode() == Transform::Mode::SCALE) glColor3d(1.0, 1.0, 1.0);
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "F3 = Scaling" );
		glColor3d(1.0, 0.0, 0.0);

	if (scene->getShowVertices())glColor3d(1.0, 1.0, 1.0);	// highlight text if vertices are shown
		renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "F4 = Show Vertices" );
		glColor3d(1.0, 0.0, 0.0);

	scene->clearFrame();
	// Flush drawing commands
    glutSwapBuffers();
}



/*void refreshFunction(int i){
	glutTimerFunc(33, refreshFunction, 1);
	glutPostRedisplay();
}*/

glm::vec2* selected_vertice;


void MouseClick(int button, int state, int x, int y){
	selected_vertice = Input::MouseClick(button, state, x, y);
}

void MouseMotion(int x, int y){
	Input::MouseMotion(selected_vertice, x, y);
}

void MousePassiveMotion(int x, int y){
	mouse_position = glm::vec2(x, y);
	glutPostRedisplay();
}

void KeyboardPressed(unsigned char key, int x, int y){
	Input::KeyboardPressed(key, x, y);
	glutPostRedisplay();
}

void KeyboardSpecialPressed(int key, int x, int y) {
	Input::KeyboardSpecialPressed(key, x, y);
	glutPostRedisplay();
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
	

	//scene->loadFrame("Pictures/line.ppm");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
 	glutCreateWindow("Computergrafik");
	glutDisplayFunc(RenderScene);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyboardPressed);
	glutSpecialFunc(KeyboardSpecialPressed);
	//glutIdleFunc(idle);
	//glutTimerFunc(33, refreshFunction, 1);

	
	glutMainLoop();
	
	
	//scene->saveFrame("Pictures/line.ppm");
	
	//std::system("Pause");

}