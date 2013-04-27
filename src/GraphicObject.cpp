#include <glm\glm.hpp>

#include "GraphicObject.h"
#include "Splines\Line.h"
#include "Color.h"

extern int width, height;

void GraphicObject::setPixel(int x, int y, Color color, unsigned char* frame) {
	if ((x>=0 && y>=0) && (x < width && y < height) ) {
		frame[(y * width + x) * 3 + 0] = color.getR();
		frame[(y * width + x) * 3 + 1] = color.getG();
		frame[(y * width + x) * 3 + 2] = color.getB();
	}
}