#include "Primitives2D/Rectangle2D.h"

extern int width, height;

Rectangle2D::Rectangle2D(){
	vertices.push_back(glm::vec2(-1, -1));
	vertices.push_back(glm::vec2(-1, -1));
	bayrzentricColor = true;
}

Rectangle2D::Rectangle2D(float firstPointX, float firstPointY, float secondPointX, float secondPointY, Color color, bool bayrzentricColor)
	: color(color), bayrzentricColor(bayrzentricColor) {
	int x1 = glm::min(width-1,  glm::max(0, static_cast<int>(firstPointX)));
	int y1 = glm::min(height-1, glm::max(0, static_cast<int>(firstPointY)));
	int x2 = glm::min(width-1,  glm::max(0, static_cast<int>(secondPointX)));
	int y2 = glm::min(height-1, glm::max(0, static_cast<int>(secondPointY)));
	vertices.push_back(glm::vec2(x1, y1));
	vertices.push_back(glm::vec2(x2, y2));
}

Rectangle2D::Rectangle2D(glm::vec2 firstPoint, glm::vec2 secondPoint, Color color, bool bayrzentricColor)
	: color(color), bayrzentricColor(bayrzentricColor) {
	Rectangle2D::Rectangle2D(firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y, color);
}

GraphicObject* Rectangle2D::copy() const {
    return new Rectangle2D(*this);
}

void Rectangle2D::addPoint(int x, int y){
	if (this->vertices.at(0) == glm::vec2(-1,-1)){
		this->vertices.at(0) = glm::vec2(x, y);
		this->isCompleted = false;
	}
	else if (this->vertices.at(1) == glm::vec2(-1,-1)){
		this->vertices.at(1) = glm::vec2(x, y);
		this->isCompleted = true;
	}
};

void Rectangle2D::draw(unsigned char* frame)
{
	if (!this->isCompleted)
		return;

	int x0 = static_cast<int>(glm::min(vertices.at(0).x, vertices.at(1).x));
	int y0 = static_cast<int>(glm::min(vertices.at(0).y, vertices.at(1).y));
	int x1 = static_cast<int>(glm::max(vertices.at(0).x, vertices.at(1).x));
	int y1 = static_cast<int>(glm::max(vertices.at(0).y, vertices.at(1).y));

	for(int y = y0; y <= y1; y++)
		for(int x = x0; x <= x1; x++)
			if (bayrzentricColor){
				float c = ((static_cast<float>(x-x0) / static_cast<float>(x1-x0)) + (static_cast<float>(y-y0) / static_cast<float>(y1-y0))) / 2;
				this->setPixel(x, y, Color(	static_cast<int>((1-c) * 255),
											static_cast<int>(c * 255), 
											255 - static_cast<int>(c * 255))
									 , frame);
			}
			else
				this->setPixel(x, y, this->color, frame);
}