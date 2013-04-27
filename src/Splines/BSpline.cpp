#include "BSpline.h"
#include "Line.h"
#include <vector>
#include <memory>

BSpline::BSpline(){
}

BSpline::BSpline(std::vector<glm::vec2> supportPoints, std::vector<float> knots, float accuracy, Color color)
	: supportPoints(supportPoints), knots(knots), accuracy(accuracy), color(color){}

void BSpline::addPoint(int x, int y){
	this->supportPoints.push_back(glm::vec2(x, y));
	this->isCompleted = false;
};

void BSpline::draw(unsigned char* frame)
{
	std::unique_ptr<glm::vec2[]> bezierPoints (new glm::vec2 [supportPoints.size() * supportPoints.size()]);
	int dimWidth = supportPoints.size();
	std::vector<glm::vec2> curvePoints;
	int polynom = 2;

	for (unsigned int i=0; i< knots.size(); i++)
		for (float t = 0; t < 1; t += this->accuracy) {
			for (int j=0; j<polynom; j++){
				for (unsigned int l = i - polynom + j; l < i; i++)
					if (j == 0)
						bezierPoints[l] = supportPoints.at(l);
					else {

					}

			}
			int x = static_cast<int>(bezierPoints[dimWidth * dimWidth-1].x);
			int y = static_cast<int>(bezierPoints[dimWidth * dimWidth-1].y);
		
			curvePoints.push_back(glm::vec2(x,y));
		}

	for (unsigned int i = 0; i < curvePoints.size()-1; i++)
		Line(curvePoints.at(i), curvePoints.at(i+1), color).draw(frame);

	/*
	Gegeben: Stüzpunkte bi und Knotenvektor t
	Berechne i so, dass ti ≤ t < ti+1,		0 ≤ i ≤ m
	for j = 0 .. n 
		for l = i-n+j .. i
			if j = 0
				b(l,0) = bl
			else {
				t’ = (t – tl) / (tl+n + 1-j – tl)
				b(l,j) = (1 – t’) * b(l-1,j-1) + t’ * b(l,j-1)
			}
	p(t) = b(i,n)
	*/
}