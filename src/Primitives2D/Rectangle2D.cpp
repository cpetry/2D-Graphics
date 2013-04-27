#include "Rectangle2D.h"

extern int width, height;

Rectangle2D::Rectangle2D(float firstPointX, float firstPointY, float secondPointX, float secondPointY, Color color, bool bayrzentricColor)
	: color(color), bayrzentricColor(bayrzentricColor) {
	int x1 = glm::min(width-1,  glm::max(0, static_cast<int>(firstPointX)));
	int y1 = glm::min(height-1, glm::max(0, static_cast<int>(firstPointY)));
	int x2 = glm::min(width-1,  glm::max(0, static_cast<int>(secondPointX)));
	int y2 = glm::min(height-1, glm::max(0, static_cast<int>(secondPointY)));
	firstPoint = glm::vec2(x1, y1);
	secondPoint = glm::vec2(x2, y2);
}

Rectangle2D::Rectangle2D(glm::vec2 firstPoint, glm::vec2 secondPoint, Color color, bool bayrzentricColor)
	: color(color), bayrzentricColor(bayrzentricColor) {
	Rectangle2D::Rectangle2D(firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y, color);
}

void Rectangle2D::addPoint(int x, int y){};

void Rectangle2D::draw(unsigned char* frame)
{
	int x0 = static_cast<int>(glm::min(firstPoint.x, secondPoint.x));
	int y0 = static_cast<int>(glm::min(firstPoint.y, secondPoint.y));
	int x1 = static_cast<int>(glm::max(firstPoint.x, secondPoint.x));
	int y1 = static_cast<int>(glm::max(firstPoint.y, secondPoint.y));

	for(int y = y0; y <= y1; y++)
		for(int x = x0; x <= x1; x++)
			if (bayrzentricColor){
				float c = ((static_cast<float>(x-x0) / static_cast<float>(x1-x0)) + (static_cast<float>(y-y0) / static_cast<float>(y1-y0))) / 2;
				this->setPixel(x, y, Color(static_cast<int>((1-c) * 255),
									 0, 
									 static_cast<int>(c * 255))
									 , frame);
			}
			else
				this->setPixel(x, y, this->color, frame);
}