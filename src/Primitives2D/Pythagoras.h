#pragma once

#include "Primitive2D.h"
#include "Rectangle2D.h"
#include "Triangle2D.h"
#include "../Splines/Line.h"

class Pythagoras : public Primitive2D
{
private:
	Triangle2D* t;
	float size;
	std::vector<Line> rAn, rGeg, rHypo;

public:
	Pythagoras();
	~Pythagoras();

	GraphicObject* Pythagoras::copy() const;
	void addPoint(int x, int y);
	void draw(unsigned char* frame);
};

