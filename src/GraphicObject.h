#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Transform.h"
#include "Color.h"

class GraphicObject{

public:
	enum Mode {LINE, CIRCLE, BEZIER, BSPLINE, RECTANGLE, TRIANGLE, POLYGON};
	static char* toString(Mode mode);

	bool isCompleted;
	std::vector<glm::vec2> vertices;
	Transform transformMatrix, transformObjToWorld, transformWorldToObj; 

	GraphicObject();
	virtual GraphicObject* copy() const=0;

	GraphicObject* operator* (Transform transform);

	virtual void addPoint(int x, int y)=0;
	virtual void draw(unsigned char* frame)=0;
	void setPixel(int x, int y, Color color, unsigned char* frame);

	void setTransformationMatrix(Transform);
	Transform getTransformationMatrix();
};
