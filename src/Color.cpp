#include "Color.h"
#include <algorithm>

Color::Color()
{
	this->r = 255;
	this->g = 255;
	this->b = 255;
}

Color::Color(int r, int g, int b)
{
	this->r = std::max(0, std::min(r, 255)); // 0 <= r <= 255
	this->g = std::max(0, std::min(g, 255)); // 0 <= g <= 255
	this->b = std::max(0, std::min(b, 255)); // 0 <= b <= 255
}

bool Color::operator== (Color const& c) const {
	if (c.r == this->r
		&& c.g == this->g
		&& c.b == this->b)
		return true;
	else
		return false;
}

unsigned char Color::getR()
{
	return r;
}
unsigned char Color::getG()
{
	return g;
}
unsigned char Color::getB()
{
	return b;
}

void Color::setR(int r)
{
	this->r = std::max(0, std::min(r, 255)); //0 <= r <= 255
}

void Color::setG(int g)
{
	this->g = std::max(0, std::min(g, 255)); //0 <= r <= 255
}

void Color::setB(int b)
{
	this->b = std::max(0, std::min(b, 255)); //0 <= r <= 255
}