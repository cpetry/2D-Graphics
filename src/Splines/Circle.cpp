
#include "Circle.h"

Circle::Circle(float posX, float posY, float radius, Color color)
	: color(color) {
	this->vertices.push_back(glm::vec2(posX,posY));
	this->vertices.push_back(glm::vec2(posX,posY + radius));
	this->isCompleted = true;
}

Circle::Circle(glm::vec2 point, float radius, Color color)
	: color(color) {
	this->vertices.push_back(point);
	this->vertices.push_back(glm::vec2(point.x + radius, point.y + radius));
	this->isCompleted = true;
}

void Circle::addPoint(int x, int y){
	if(this->vertices.at(0).x == -1 && this->vertices.at(0).y == -1){
		this->vertices.at(0) = glm::vec2(x,y);
		this->isCompleted = false;
	}
	else if(this->vertices.at(1) == glm::vec2(-1,-1)){
		float distance = std::sqrt(std::pow(std::abs(this->vertices.at(0).x - x), 2) + std::pow(std::abs(this->vertices.at(0).y - y), 2));
		this->vertices.at(1) = glm::vec2(this->vertices.at(0).x + distance, this->vertices.at(0).y);
		this->isCompleted = true;
	}
};

GraphicObject* Circle::copy() const {
	Circle * l = new Circle(*this);
	l->vertices = this->vertices;
    return l;
}

void Circle::draw(unsigned char* frame)
{
	if (!this->isCompleted)
		return;

	int x = static_cast<int>(this->vertices.at(0).x);
	int y = static_cast<int>(this->vertices.at(0).y);

	int radius = static_cast<int>(std::sqrt(
						std::pow(std::abs(x - this->vertices.at(1).x), 2) + 
						std::pow(std::abs(y - this->vertices.at(1).y), 2)));

	int x1 = 0;
	int y1 = radius;
	int f  = 1 - radius;
	int dx = 3;
	int dy = 2 - 2*radius;

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