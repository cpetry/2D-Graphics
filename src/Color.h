#pragma once

/**
 *@brief: defines a color in 8bit for rgb
 */
class Color
{
private:
	unsigned char r,g,b;

public:
	Color();
	Color(int r, int g, int b);
	bool operator==(Color const& c)  const ;
	unsigned char getR();
	unsigned char getG();
	unsigned char getB();
	void Color::setR(int r);
	void Color::setG(int g);
	void Color::setB(int b);
};