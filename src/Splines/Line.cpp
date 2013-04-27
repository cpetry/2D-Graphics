#include <glm\glm.hpp>
#include <glut.h>

#include "Line.h"
class Color;

extern int width, height;

// vec2 Point1, vec2 Point2, Color
Line::Line(glm::vec2 p1, glm::vec2 p2, Color color)
	: points(p1,p2), color(color){}

// Coordinates Point1, Coordinates Point2, Color
Line::Line(int x1, int y1, int x2, int y2, Color color)
	: points(glm::vec2(x1,y1), glm::vec2(x2,y2)), color(color){}

// Coordinates Point1, degree and distance
Line::Line(int x1, int y1, float deg, int distance, Color color)
	: color(color)
{
	// clamping x and y between 0 and width/height
	int x2 = glm::min(width-1,  glm::max(0, static_cast<int>(x1 + distance*cos(glm::radians(deg)))));
	int y2 = glm::min(height-1, glm::max(0, static_cast<int>(y1 + distance*sin(glm::radians(deg)))));
	points.first  = glm::vec2(x1,y2);
	points.second = glm::vec2(x2,y2);
}

void Line::addPoint(int x, int y){
	if(points.first.x == -1 && points.first.y == -1){
		this->points.first = glm::vec2(x,y);
		this->points.second = glm::vec2(x,y);
		this->isCompleted = false;
	}
	else {
		this->points.second = glm::vec2(x,y);
		this->isCompleted = true;
	}
}

void Line::draw(unsigned char* frame)
{
	// getting deltas
	int dx = static_cast<int>(points.second.x) - static_cast<int>(points.first.x);
	int dy = static_cast<int>(points.second.y) - static_cast<int>(points.first.y);

	// getting direction of x and y
	int incrX = glm::sign(dx);
	int incrY = glm::sign(dy);
	dx = abs(dx);
	dy = abs(dy);

	int error, errSteady, errChange, steadyX, steadyY;
	// finding out which direction grows faster
	if (dx>dy){
		// x is growing steadily
		errSteady = dx;
		errChange = dy;
		steadyX = incrX;
		steadyY = 0;
	}
	
	else{
		// y is growing steadily
		errSteady = dy;
		errChange = dx;
		steadyX = 0;
		steadyY = incrY;
	}
	
	// changing direction always increments both
	int changeX, changeY;
	changeX = incrX;
	changeY = incrY;

	// Setting startpoint;
	int x = static_cast<int>(points.first.x);
	int y = static_cast<int>(points.first.y);
	error = errSteady / 2;
	this->setPixel(x, y, this->color, frame);

	// walking step for step till deltasteady
	for (int step=0; step < errSteady; step++)
	{ 
		error -= errChange;
		if (error < 0)	// Richtung justieren
		{
			// gehe in unstetige Richtung
			error += errSteady;	// Fehler wieder positiv machen
			x += changeX;
			y += changeY;
		}
		else			// einfach weiter gehen
		{
			x += steadyX;
			y += steadyY;
		}
		this->setPixel(x, y, this->color, frame);
	}
}