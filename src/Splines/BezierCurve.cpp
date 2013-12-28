#include "Splines/BezierCurve.h"
#include "Splines/Line.h"
#include <vector>
#include <memory>

BezierCurve::BezierCurve(){
	this->accuracy = 0.02f;
}

BezierCurve::BezierCurve(std::vector<glm::vec2> supportPoints, float accuracy, Color color)
	: color(color)
{
	this->vertices = supportPoints;
	if (accuracy >= 1.0f || accuracy <= 0.0f)
		this->accuracy = 0.2 / supportPoints.size();
	else
		this->accuracy = accuracy;
}

GraphicObject* BezierCurve::copy() const {
    return new BezierCurve(*this);
}

void BezierCurve::addPoint(int x, int y){
	this->accuracy = 0.2 / vertices.size();
	this->vertices.push_back(glm::vec2(x, y));
	this->isCompleted = false;
};

void BezierCurve::draw(unsigned char* frame)
{
	std::unique_ptr<glm::vec2[]> bezierPoints (new glm::vec2 [vertices.size() * vertices.size()]);
	int dimWidth = vertices.size();
	std::vector<glm::vec2> curvePoints;

	for (int i=0; i<dimWidth; i++){
		bezierPoints[i*dimWidth + 0] = vertices.at(i);
	}

	for (float t = 0; t < 1; t += this->accuracy) {
		for (int j=1; j<dimWidth; j++){
			for (int i=j; i<dimWidth; i++)
				bezierPoints[i*dimWidth + j] = bezierPoints[(i-1)*dimWidth + j-1] * (1-t) + bezierPoints[i*dimWidth + j-1] * t ;
		}
		int x = static_cast<int>(bezierPoints[dimWidth * dimWidth-1].x);
		int y = static_cast<int>(bezierPoints[dimWidth * dimWidth-1].y);
		
		curvePoints.push_back(glm::vec2(x,y));
	}

	// add the last vector to the points of the curve
	curvePoints.push_back(this->vertices.at(this->vertices.size() - 1));

	for (unsigned int i = 0; i < curvePoints.size()-1; i++)
		Line(curvePoints.at(i), curvePoints.at(i+1), color).draw(frame);
	/*
	for i = 0 .. n
		b(i,0) = bi
	for j = 1 .. n 
		for i = j .. n
			b(i,j) = (1-t) * b(i-1,j-1) + t * b(i,j-1)
	p(t) = b(n,n)*/
}