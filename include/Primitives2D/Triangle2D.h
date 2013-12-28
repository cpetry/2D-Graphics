#pragma once

#include "Primitive2D.h"
#include "Color.h"

class Triangle2D : public Primitive2D{
private:
	bool bayrzentricColor;
	Color color;
	glm::vec2 center;

public:
	Triangle2D();
	Triangle2D(float firstPointX, float firstPointY, float secondPointX, float secondPointY, float thirdPointX, float thirdPointY, Color color = Color(), bool bayrzentricColor = false);
	Triangle2D(glm::vec2 firstPoint, glm::vec2 secondPoint, glm::vec2 thirdPoint, Color color = Color(), bool bayrzentricColor = false);
	
	GraphicObject* Triangle2D::copy() const;

	void addPoint(int x, int y);

	bool operator==(Triangle2D const& t)  const ;
	void draw(unsigned char* frame);

	glm::vec2 getCenter();
};