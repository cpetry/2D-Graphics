#include <glm\glm.hpp>
#include <glut.h>

#include "Line.h"
class Color;

extern int width, height;

// vec2 Point1, vec2 Point2, Color
Line::Line(glm::vec2 p1, glm::vec2 p2, Color color)
	: color(color){
		vertices.push_back(p1);
		vertices.push_back(p2);
}

// Coordinates Point1, Coordinates Point2, Color
Line::Line(int x1, int y1, int x2, int y2, Color color)
	: color(color){
		vertices.push_back(glm::vec2(x1,y2));
		vertices.push_back(glm::vec2(x2,y2));
}
// Coordinates Point1, degree and distance
Line::Line(int x1, int y1, float deg, int distance, Color color)
	: color(color)
{
	// clamping x and y between 0 and width/height
	int x2 = glm::min(width-1,  glm::max(0, static_cast<int>(x1 + distance*cos(glm::radians(deg)))));
	int y2 = glm::min(height-1, glm::max(0, static_cast<int>(y1 + distance*sin(glm::radians(deg)))));
	vertices.push_back(glm::vec2(x1,y2));
	vertices.push_back(glm::vec2(x2,y2));
}

GraphicObject* Line::copy() const {
	Line * l = new Line(*this);
	l->vertices = this->vertices;
    return l;
}

void Line::addPoint(int x, int y){
	if(vertices.at(0).x == -1 && vertices.at(0).y == -1){
		this->vertices.at(0) = glm::vec2(x,y);
		this->vertices.at(1) = glm::vec2(x,y);
		this->isCompleted = false;
	}
	else {
		this->vertices.at(1) = glm::vec2(x,y);
		this->isCompleted = true;
	}
}

void Line::draw(unsigned char* frame)
{
	this->bresenhamAlgorithm(frame);
	//this->midpointAlgorithm(frame);
}

void Line::midpointAlgorithm(unsigned char* frame){
	int x1 = vertices.at(0).x;
	int y1 = vertices.at(0).y;
	int x2 = vertices.at(1).x;
	int y2 = vertices.at(1).y;
	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	int f = dy - static_cast<int>(dx / 2.0f);

	int incrfar=0;
	int incrnear=0;
	
	int lfar, lnear, deltafar, deltanear;
	if (dy > dx){
		deltafar = dy;
		deltanear = dx;
		lfar = y1;
		lnear = x1;
		if (y1 > y2)
			incrfar = -1;
		else
			incrfar = +1;
		if (x1 > x2)
			incrnear = -1;
		else
			incrnear = +1;
	}
	else{
		deltafar = dx;
		deltanear = dy;
		lfar = x1;
		lnear = y1;
		if (y1 > y2)
			incrnear = -1;
		else
			incrnear = +1;
		if (x1 > x2)
			incrfar = -1;
		else
			incrfar = +1;
	}

	for (int i = 1; i < deltafar; i++) {
		if (dy > dx)
			this->setPixel(lnear, lfar, this->color, frame);
		else
			this->setPixel(lfar, lnear, this->color, frame);

		lfar += incrfar;
		if (f > 0) {
			lnear += incrnear;
			f -= deltafar;
		}
		f += deltanear;
	}
}

void Line::bresenhamAlgorithm(unsigned char* frame){
	// getting deltas
	int dx = static_cast<int>(vertices.at(1).x) - static_cast<int>(vertices.at(0).x);
	int dy = static_cast<int>(vertices.at(1).y) - static_cast<int>(vertices.at(0).y);

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
	int x = static_cast<int>(vertices.at(0).x);
	int y = static_cast<int>(vertices.at(0).y);
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
		else // einfach weiter gehen
		{
			x += steadyX;
			y += steadyY;
		}
		this->setPixel(x, y, this->color, frame);
	}
}