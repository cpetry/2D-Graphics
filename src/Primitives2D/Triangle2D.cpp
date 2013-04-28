#include "Triangle2D.h"

extern int width, height;

Triangle2D::Triangle2D(){
	color = Color();
	this->firstPoint  = glm::vec2(-1, -1);
	this->secondPoint = glm::vec2(-1, -1);
	this->thirdPoint  = glm::vec2(-1, -1);
	bayrzentricColor = true;
}

Triangle2D::Triangle2D(float firstPointX, float firstPointY, float secondPointX, float secondPointY, float thirdPointX, float thirdPointY, Color color, bool bayrzentricColor)
	: color(color), bayrzentricColor(bayrzentricColor) {
	int x1 = glm::min(width-1,  glm::max(0, static_cast<int>(firstPointX)));
	int y1 = glm::min(height-1, glm::max(0, static_cast<int>(firstPointY)));
	int x2 = glm::min(width-1,  glm::max(0, static_cast<int>(secondPointX)));
	int y2 = glm::min(height-1, glm::max(0, static_cast<int>(secondPointY)));
	int x3 = glm::min(width-1,  glm::max(0, static_cast<int>(thirdPointX)));
	int y3 = glm::min(height-1, glm::max(0, static_cast<int>(thirdPointY)));

	this->firstPoint  = glm::vec2(x1, y1);
	this->secondPoint = glm::vec2(x2, y2);
	this->thirdPoint  = glm::vec2(x3, y3);
}

Triangle2D::Triangle2D(glm::vec2 firstPoint, glm::vec2 secondPoint, glm::vec2 thirdPoint, Color color, bool bayrzentricColor)
	: color(color), bayrzentricColor(bayrzentricColor) {
	int x1 = glm::min(width-1,  glm::max(0, static_cast<int>(firstPoint.x)));
	int y1 = glm::min(height-1, glm::max(0, static_cast<int>(firstPoint.y)));
	int x2 = glm::min(width-1,  glm::max(0, static_cast<int>(secondPoint.x)));
	int y2 = glm::min(height-1, glm::max(0, static_cast<int>(secondPoint.y)));
	int x3 = glm::min(width-1,  glm::max(0, static_cast<int>(thirdPoint.x)));
	int y3 = glm::min(height-1, glm::max(0, static_cast<int>(thirdPoint.y)));

	this->firstPoint  = glm::vec2(x1, y1);
	this->secondPoint = glm::vec2(x2, y2);
	this->thirdPoint  = glm::vec2(x3, y3);
}

void Triangle2D::addPoint(int x, int y){
	if (this->firstPoint == glm::vec2(-1,-1)){
		this->firstPoint = glm::vec2(x, y);
		this->isCompleted = false;
	}
	else if (this->secondPoint == glm::vec2(-1,-1)){
		this->secondPoint = glm::vec2(x, y);
		this->isCompleted = false;
	}
	else if (this->thirdPoint == glm::vec2(-1,-1)){
		this->thirdPoint = glm::vec2(x, y);

		// testing if triangle is counterclockwise, if not rearrange!
		int d = firstPoint.x*secondPoint.y + secondPoint.x*thirdPoint.y + thirdPoint.x*firstPoint.y 
			   - secondPoint.y*thirdPoint.x - thirdPoint.y*firstPoint.x - firstPoint.y*secondPoint.x;
		if (d < 0){
			glm::vec2 saveVec = secondPoint;
			secondPoint = thirdPoint;
			thirdPoint = saveVec;
		}

		this->isCompleted = true;
	}
}

bool Triangle2D::operator== (Triangle2D const& t) const {
	if (this->firstPoint == t.firstPoint
		&& this->secondPoint == t.secondPoint
		&& this->thirdPoint == t.thirdPoint)
		return true;
	else
		return false;
}

void Triangle2D::draw(unsigned char* frame)
{
	if (!this->isCompleted)
		return;

	int x0 = static_cast<int>(firstPoint.x);	
	int y0 = static_cast<int>(firstPoint.y);
	int x1 = static_cast<int>(secondPoint.x);
	int y1 = static_cast<int>(secondPoint.y);
	int x2 = static_cast<int>(thirdPoint.x);
	int y2 = static_cast<int>(thirdPoint.y);

	

	int xmin = glm::min(x0, glm::min(x1,x2));
	int ymin = glm::min(y0, glm::min(y1,y2));
	int xmax = glm::max(x0, glm::max(x1,x2));
	int ymax = glm::max(y0, glm::max(y1,y2));
	int f0 = (y0-y1)*(xmin-x0) + (x1-x0)*(ymin-y0);
	int f1 = (y1-y2)*(xmin-x1) + (x2-x1)*(ymin-y1);
	int f2 = (y2-y0)*(xmin-x2) + (x0-x2)*(ymin-y2);
	
	for(int y = ymin; y<=ymax; y++) {
		int ff0 = f0, ff1 = f1, ff2 = f2;
		for(int x = xmin; x<=xmax; x++) {
			if(ff0 >= 0 && ff1 >=0 && ff2 >= 0) {
				int c = ff0 + ff1 + ff2;
				if (bayrzentricColor){
					int red = 1.0f/c * ff0 * 255;
					int green = 1.0f/c * ff1 * 255;
					int blue = 1.0f/c * ff2 * 255;
					this->setPixel(x, y, Color( red, green, blue), frame);
				}
				else{
					this->setPixel(x, y, color, frame);
				}
			}
			ff0 = ff0 + (y0-y1);
			ff1 = ff1 + (y1-y2);
			ff2 = ff2 + (y2-y0);
		}
		f0 = f0 + (x1-x0);
		f1 = f1 + (x2-x1);
		f2 = f2 + (x0-x2);
	} 	
}