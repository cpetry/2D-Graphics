#define FREEGLUT_STATIC

#include <windows.h>		// Must have for Windows platform builds
#include <vector>
#include "gl/glew.h"
#include <glut.h>
#include <memory>
#include <string>


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
	std::string mode_text = "Mode: ";
	mode_text += GraphicObject::toString(scene->getGraphicObjectMode());
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - 20, GLUT_BITMAP_9_BY_15, mode_text.c_str());
	
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "Commands: " );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "l = Line" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "c = circle" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "b = bezier" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "s = bspline" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "r = rectangle" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "t = triangle" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "p = polygon" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "F1 = Translation" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "F2 = Rotation" );
	renderBitmapString(0, glutGet( GLUT_WINDOW_HEIGHT ) - (linestart + linenum++ * lineheight), GLUT_BITMAP_9_BY_15, "F3 = Scaling" );

	scene->clearFrame();
	// Flush drawing commands
    glutSwapBuffers();
}



/*void refreshFunction(int i){
	glutTimerFunc(33, refreshFunction, 1);
	glutPostRedisplay();
}*/

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
	glutMouseFunc(&Input::MouseClick);
	glutKeyboardFunc(KeyboardPressed);
	glutSpecialFunc(KeyboardSpecialPressed);
	//glutIdleFunc(idle);
	//glutTimerFunc(33, refreshFunction, 1);

	
	glutMainLoop();
	
	
	//scene->saveFrame("Pictures/line.ppm");
	
	//std::system("Pause");

}