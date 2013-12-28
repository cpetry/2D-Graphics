#pragma once

#include <glm\glm.hpp>
#include <vector>
#include "Color.h"
#include "Splines\Spline.h"

class Line : public Spline {
private:
	
	Color color;

	void bresenhamAlgorithm(unsigned char* frame);
	void midpointAlgorithm(unsigned char* frame);

public:
	Line(){ vertices.push_back(glm::vec2(-1,-1)); vertices.push_back(glm::vec2(-1,-1));};
	Line(glm::vec2 p1, glm::vec2 p2, Color color = Color());
	Line(int x1, int y1, int x2, int y2,  Color color = Color());
	Line(int x1, int y1, float deg, int distance, Color color = Color());
	
	GraphicObject* copy() const;

	void operator*(Transform transform);

	void addPoint(int x, int y);

	void draw(unsigned char* frame);
};