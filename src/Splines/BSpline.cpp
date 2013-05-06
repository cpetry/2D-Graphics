#include "BSpline.h"
#include "Line.h"
#include <vector>
#include <memory>

BSpline::BSpline(){
	this->polynom = 2;
	color = Color(255,255,255);
}

BSpline::BSpline(std::vector<glm::vec2> supportPoints, float accuracy, Color color)
	: color(color){
		this->polynom = 2;
		this->vertices = supportPoints;
}

GraphicObject* BSpline::copy() const {
    return new BSpline(*this);
}

void BSpline::addPoint(int x, int y){
	this->vertices.push_back(glm::vec2(x, y));
	this->isCompleted = false;
	this->knots.clear();

	for (int p = 0; p < this->polynom; p++)
		this->knots.push_back(0);
	
	for (int p = 0; p < vertices.size(); p++)
		this->knots.push_back(1.0F - (vertices.size() * 1.0F / (vertices.size() + p) * 1.0F));

	for (int p = 0; p < this->polynom; p++)
		this->knots.push_back(1);


	this->accuracy = 0.05 / vertices.size();
};

void BSpline::draw(unsigned char* frame){
	this->drawOpenBSplineCurve(frame);
	//this->drawClosedBSplineCurve(frame);
}

void BSpline::drawOpenBSplineCurve(unsigned char* frame)
{
	if (this->vertices.size() < 2)
		return;
	else if (this->vertices.size() == 2){
		Line(vertices.at(0), vertices.back(), color).draw(frame);
		return;
	}

	std::vector<std::vector<glm::vec2>> bezierPoints;
	int dimWidth = vertices.size();
	std::vector<glm::vec2> curvePoints;


	for (int i=0; i < dimWidth; i++)
		bezierPoints.push_back(std::vector<glm::vec2>(vertices.size()));

	for (unsigned int i=0; i<this->vertices.size(); i++){
		for (float t = knots.at(i); t < knots.at(i+1); t += this->accuracy) {
		
			// berechne den Index i so, dass ti <= t* < ti+1
			for (unsigned int j = 0; j <= polynom; j++){
				for (unsigned int l = i-polynom+j; l <= i; l++){
					if (j == 0)
						bezierPoints.at(0).at(l) = this->vertices.at(l);
					else {
						float t_marked = (t - knots.at(l)) / (knots.at(l+polynom+1-j) - knots.at(l));
						bezierPoints.at(j).at(l) = ((1-t_marked) * bezierPoints.at(j-1).at(l-1)) + (t_marked * bezierPoints.at(j-1).at(l));
					}
				}
			}
			int x = static_cast<int>(bezierPoints.at(polynom).at(i).x);
			int y = static_cast<int>(bezierPoints.at(polynom).at(i).y);
		
			curvePoints.push_back(glm::vec2(x,y));
		}
	}
	for (unsigned int i = 0; i < curvePoints.size()-1; i++)
		Line(curvePoints.at(i), curvePoints.at(i+1), color).draw(frame);

	Line(curvePoints.back(), vertices.back(), color).draw(frame);
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