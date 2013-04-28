#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Transform.h"
#include "Color.h"

class GraphicObject{

public:
	enum Mode {LINE, CIRCLE, BEZIER, BSPLINE, RECTANGLE, TRIANGLE, POLYGON};
	bool isCompleted;
	std::vector<glm::vec2> vertices;
	Transform transformMatrix, transformObjToWorld, transformWorldToObj; 

	GraphicObject();

	virtual void addPoint(int x, int y)=0;
	virtual void draw(unsigned char* frame)=0;
	GraphicObject* GraphicObject::operator* (const Transform transform);
	void setPixel(int x, int y, Color color, unsigned char* frame);

	void setTransformationMatrix(Transform);
	Transform getTransformationMatrix();
};
