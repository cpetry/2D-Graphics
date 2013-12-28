#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Transform.h"
#include "Color.h"

class GraphicObject{

public:
	enum Mode {SELECTION, LINE, CIRCLE, BEZIER, BSPLINE, RECTANGLE, TRIANGLE, POLYGON, PYTHAGORAS};
	static char* toString(Mode mode);

	bool isCompleted;
	std::vector<glm::vec2> vertices;
	glm::vec2 pivot;
	Transform transformMatrix; 

	GraphicObject();
	virtual GraphicObject* copy() const=0;

	GraphicObject* operator* (Transform transform);

	virtual void addPoint(int x, int y)=0;
	virtual void draw(unsigned char* frame)=0;
	void setPixel(int x, int y, Color color, unsigned char* frame);

	void setTransformationMatrix(Transform);
	Transform getTransformationMatrix();

	std::vector<glm::vec2> getVertices();
	glm::vec2 getPivot();
	void calcPivot();
};
