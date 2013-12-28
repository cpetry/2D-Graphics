#pragma once
#include <vector>
#include "Spline.h"
#include "Color.h"

class BSpline : public Spline{
private:
	std::vector<glm::vec2> supportPoints;
	std::vector<float> knots;
	int polynom;
	float accuracy;
	Color color;
public:
	BSpline();
	BSpline(std::vector<glm::vec2> supportPoints, float accuracy, Color color = Color());

	GraphicObject* BSpline::copy() const;

	void addPoint(int x, int y);

	void draw(unsigned char* frame);

	void drawOpenBSplineCurve(unsigned char* frame);
	void drawClosedBSplineCurve(unsigned char* frame);
};