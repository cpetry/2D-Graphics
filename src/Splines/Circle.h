#pragma once

#include "Spline.h"
#include "Color.h"

class Circle : public Spline{
private:
	Color color;

public:
	Circle(){ this->vertices.push_back(glm::vec2(-1,-1)); this->vertices.push_back(glm::vec2(-1,-1)); this->isCompleted = false;};
	Circle(float posX, float posY, float radius, Color color = Color());
	Circle(glm::vec2 point, float radius, Color color = Color());

	GraphicObject* copy() const;

	void addPoint(int x, int y);

	void draw(unsigned char* frame);
};