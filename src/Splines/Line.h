#pragma once

#include <glm\glm.hpp>
#include <vector>
#include "Color.h"
#include "Splines\Spline.h"

class Line : public Spline {
private:
	std::pair<glm::vec2, glm::vec2> points;
	Color color;

public:
	Line::Line(){ points.first = glm::vec2(-1,-1); points.second = glm::vec2(-1,-1);};
	Line(glm::vec2 p1, glm::vec2 p2, Color color = Color());
	Line(int x1, int y1, int x2, int y2,  Color color = Color());
	Line(int x1, int y1, float deg, int distance, Color color = Color());

	void addPoint(int x, int y);

	void draw(unsigned char* frame);
};