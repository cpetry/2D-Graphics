#include <glm\glm.hpp>
#include <set>

#include "Polygon2D.h"
#include "Splines/Line.h"
#include "Scene.h"
#include "Color.h"

extern int width, height;

Polygon2D::Polygon2D(){}

Polygon2D::Polygon2D(std::vector<glm::vec2> points, Color color)
: color(color) {
	this->vertices = points;
}

GraphicObject* Polygon2D::copy() const {
    return new Polygon2D(*this);
}


void Polygon2D::addPoint(int x, int y){
	this->vertices.push_back(glm::vec2(x,y));
	this->isCompleted = false;
}

void Polygon2D::draw(unsigned char* frame){

	// find min and max y-values
	auto miny = vertices.at(0).y, maxy = vertices.at(0).y;
	for (glm::vec2 p : vertices){
		miny = std::min(miny, p.y);
		maxy = std::max(maxy, p.y);
	}
	
	// calculate intersections
	for (int yline = static_cast<int>(miny); yline < maxy; yline++){
		std::set<float> intersectionPoints;
		for (unsigned int i=0; i < vertices.size()-1; i++) {
			if (vertices.at(i).y >= yline && vertices.at(i+1).y <= yline
			||vertices.at(i).y <= yline && vertices.at(i+1).y >= yline){
				float m = (vertices.at(i).y - vertices.at(i+1).y) / (vertices.at(i).x - vertices.at(i+1).x);
				// y = m*(x + b1) + c1;  y = c2   =>  c2 = m*(x+b1) + c1  =>  x = (c2 - c1) / m + b1 
				float x = ((yline - vertices.at(i).y) / m) + vertices.at(i).x;
				intersectionPoints.insert(x);
			}
		}

		for (auto p = intersectionPoints.begin(); p != (--intersectionPoints.end()) && p != intersectionPoints.end(); p++){
			int xbegin = static_cast<int>(*p), xend = static_cast<int>(*(++p));
			for (int x = xbegin; x <= xend; x++)
				this->setPixel(x, yline, this->color, frame);
		}
		intersectionPoints.clear();
	}

	
	

}