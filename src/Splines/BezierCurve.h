#pragma once
#include <vector>
#include "Spline.h"
#include "Color.h"

class BezierCurve : public Spline{
private:
	std::vector<glm::vec2> supportPoints;
	float accuracy;
	Color color;
public:
	BezierCurve();
	BezierCurve(std::vector<glm::vec2> supportPoints, float accuracy, Color color = Color());

	GraphicObject* BezierCurve::copy() const;

	void addPoint(int x, int y);

	void draw(unsigned char* frame);
};