#include <glm\glm.hpp>
#include <set>

#include "Polygon2D.h"
#include "Splines/Line.h"
#include "Scene.h"
#include "Color.h"

extern int width, height;

Polygon2D::Polygon2D(std::vector<glm::vec2> points, Color color)
: points(points), color(color) {}

void Polygon2D::addPoint(int x, int y){
	this->points.push_back(glm::vec2(x,y));
}

void Polygon2D::draw(unsigned char* frame){

	// find min and max y-values
	auto miny = points.at(0).y, maxy = points.at(0).y;
	for (glm::vec2 p : points){
		miny = std::min(miny, p.y);
		maxy = std::max(maxy, p.y);
	}
	
	// calculate intersections
	for (int yline = static_cast<int>(miny); yline < maxy; yline++){
		std::set<float> intersectionPoints;
		for (unsigned int i=0; i < points.size()-1; i++) {
			if (points.at(i).y >= yline && points.at(i+1).y <= yline
			||points.at(i).y <= yline && points.at(i+1).y >= yline){
				float m = (points.at(i).y - points.at(i+1).y) / (points.at(i).x - points.at(i+1).x);
				// y = m*(x + b1) + c1;  y = c2   =>  c2 = m*(x+b1) + c1  =>  x = (c2 - c1) / m + b1 
				float x = ((yline - points.at(i).y) / m) + points.at(i).x;
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