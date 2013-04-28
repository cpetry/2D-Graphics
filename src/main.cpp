#define FREEGLUT_STATIC

#include <windows.h>		// Must have for Windows platform builds
#include <vector>
#include "gl/glew.h"
#include <glut.h>
#include <memory>


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

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	scene->drawAllGraphicObjects();

	glDrawPixels(scene->getFrameWidth(), scene->getFrameHeight(), GL_RGB, GL_UNSIGNED_BYTE, scene->getFrame());

	scene->clearFrame();
	// Flush drawing commands
    glFlush();
}



///////////////////////////////////////////////////////////
// Setup the rendering state
void SetupRC(void)
{

	////////////////////////
	//Lines
	/*
	for (float degree = 0; degree < 360; degree += 5.125){
		color.setR(255 * degree / 360);
		color.setG(255 * degree / 360);
		color.setB(255 * degree / 360);
		scene->add(new Line(width/2, height/2, degree, 100, color));
	}*/

	
	////////////////////////
	//Circle
	//	scene->add(new Circle(100, 300, 100, Color(255,0,0)));

	
	////////////////////////
	//BezierCurve
	/*
	// Creating bezier curve
	std::vector<glm::vec2> bezierCurve;
	bezierCurve.push_back(glm::vec2(100, 100));
	bezierCurve.push_back(glm::vec2(800, 350));
	bezierCurve.push_back(glm::vec2(300, 500));
	bezierCurve.push_back(glm::vec2(600, 600));
	bezierCurve.push_back(glm::vec2(500, 700));

	// adding points of bezier curve
	//for (glm::vec2 bezierPoint : bezierCurve)
	//	scene->add(new Circle(bezierPoint.x, bezierPoint.y, 2, Color(255,255,0)));

	// adding bezier Curve
	//scene->add(new BezierCurve(bezierCurve, 0.02f, Color(0,255,0)));
	*/

	////////////////////////
	//BSplineCurve
	/*
	// Creating bspline curve
	std::vector<glm::vec2> bsplineCurve;
	bsplineCurve.push_back(glm::vec2(100, 100));
	bsplineCurve.push_back(glm::vec2(800, 350));
	bsplineCurve.push_back(glm::vec2(300, 500));
	bsplineCurve.push_back(glm::vec2(600, 600));
	bsplineCurve.push_back(glm::vec2(800, 700));
	bsplineCurve.push_back(glm::vec2(900, 750));

	// adding points of bspline curve
	for (glm::vec2 bsplinePoint : bsplineCurve)
		scene->add(new Circle(bsplinePoint.x, bsplinePoint.y, 2.0f, Color(255,255,0)));

	// adding bspline Curve
	std::vector<float> knots;
	knots.push_back(0);
	knots.push_back(0);
	knots.push_back(0);
	knots.push_back(0.2f);
	knots.push_back(0.6f);
	knots.push_back(0.9f);
	knots.push_back(1.0f);
	knots.push_back(1.0f);
	knots.push_back(1.0f);
	scene->add(new BSpline(bsplineCurve, knots, Color(0,255,0)));
	*/

	////////////////////////
	//Rectangle
	//scene->add(new Rectangle2D(100, 500, 300, 800, Color(), true));

	////////////////////////
	//Triangle
	//scene->add(new Triangle2D(400.0f, 400.0f, 600.0f, 550.0f, 350.0f, 500.0f, Color(150,0,150), true));
	//scene->add(new Triangle2D(glm::vec2(100.0f, 100.0f), glm::vec2(600.0f, 550.0f), glm::vec2(150.0f, 500.0f), Color(), true));
	

	//Polygon
	/*
	std::vector<glm::vec2> pointList;
	pointList.push_back(glm::vec2(100.0f, 100.0f));
	pointList.push_back(glm::vec2(100.0f, 200.0f));
	pointList.push_back(glm::vec2(200.0f, 100.0f));
	pointList.push_back(glm::vec2(200.0f, 200.0f));
	pointList.push_back(glm::vec2(100.0f, 100.0f));
	scene->add(new Polygon2D(pointList, Color()));*/
}

void idle(){
	glutPostRedisplay();
}
///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
	

	//scene->loadFrame("Pictures/line.ppm");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
 	glutCreateWindow("Computergrafik");
	glutDisplayFunc(RenderScene);
	glutMouseFunc(&Input::MouseClick);
	glutKeyboardFunc(&Input::KeyboardPressed);
	glutSpecialFunc(&Input::KeyboardSpecialPressed);
	glutIdleFunc(idle);

	SetupRC();
	
	glutMainLoop();
	
	
	//scene->saveFrame("Pictures/line.ppm");
	
	//std::system("Pause");

}