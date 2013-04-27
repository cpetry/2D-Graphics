#pragma once

#include "Spline.h"
#include "Color.h"

class Circle : public Spline{
private:
	glm::vec2 point;
	float radius;
	Color color;

public:
	Circle(){ this->point = glm::vec2(-1,-1); this->radius = -1;};
	Circle(float posX, float posY, float radius, Color color = Color());
	Circle(glm::vec2 point, float radius, Color color = Color());

	void addPoint(int x, int y);

	void draw(unsigned char* frame);
};