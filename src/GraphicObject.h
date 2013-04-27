#pragma once

#include <glm/glm.hpp>
#include "Color.h"

class GraphicObject{

public:
	enum Mode {LINE, CIRCLE, BEZIER, BSPLINE, RECTANGLE, TRIANGLE, POLYGON};
	bool isCompleted;

	virtual void addPoint(int x, int y)=0;
	virtual void draw(unsigned char* frame)=0;
	void setPixel(int x, int y, Color color, unsigned char* frame);
};
