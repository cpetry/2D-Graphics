#pragma once
#include <vector>
#include "Spline.h"
#include "Color.h"

class BSpline : public Spline{
private:
	std::vector<glm::vec2> supportPoints;
	std::vector<float> knots;
	float accuracy;
	Color color;
public:
	BSpline();
	BSpline(std::vector<glm::vec2> supportPoints, std::vector<float> knots, float accuracy, Color color = Color());

	void addPoint(int x, int y);


	void draw(unsigned char* frame);
};