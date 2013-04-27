
#include "Circle.h"

Circle::Circle(float posX, float posY, float radius, Color color)
	: point(posX, posY), radius(radius), color(color) {}

Circle::Circle(glm::vec2 point, float radius, Color color)
	: point(point), radius(radius), color(color) {}

void Circle::addPoint(int x, int y){
	if(point.x == -1 && point.y == -1){
		this->point = glm::vec2(x,y);
		this->isCompleted = false;
	}
	else if(radius == -1){
		this->radius = std::sqrt(std::pow(std::abs(point.x - x), 2) + std::pow(std::abs(point.y - y), 2));
		this->isCompleted = true;
	}
};

void Circle::draw(unsigned char* frame)
{
	int x = static_cast<int>(this->point.x);
	int y = static_cast<int>(this->point.y);

	int x1 = 0;
	int y1 = static_cast<int>(radius);
	int f  = 1 - static_cast<int>(radius);
	int dx = 3;
	int dy = 2 - 2*static_cast<int>(radius);

	while(x1<=y1) {
		this->setPixel(x - x1, y + y1, color, frame);
		this->setPixel(x + x1, y + y1, color, frame);
		this->setPixel(x - x1, y - y1, color, frame);
		this->setPixel(x + x1, y - y1, color, frame);

		this->setPixel(x + y1, y - x1, color, frame);
		this->setPixel(x + y1, y + x1, color, frame);
		this->setPixel(x - y1, y - x1, color, frame);
		this->setPixel(x - y1, y + x1, color, frame);
		x1++;
		if(f > 0) {
			y1--;
			f += dy;
			dy += 2;
		} 
		f += dx;
		dx +=2;
	}
}