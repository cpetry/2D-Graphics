#include <glm\glm.hpp>

#include "GraphicObject.h"
#include "Transform.h"
#include "Scene.h"
#include <memory>
#include "Splines\Line.h"
#include "Color.h"

extern int width, height;
extern std::unique_ptr<Scene> scene;

GraphicObject::GraphicObject(){
	this->transformObjToWorld = Transform::translate(-scene->getFrameWidth()/2.0f, -scene->getFrameHeight()/2.0f);
	this->transformWorldToObj = Transform::translate(scene->getFrameWidth()/2.0f, scene->getFrameHeight()/2.0f);
}

GraphicObject* GraphicObject::operator* (Transform transform){
	std::vector<glm::vec2> newvertices;
	for (auto v : this->vertices)
		newvertices.push_back(transform * v);
	this->vertices = newvertices;
	return this;
}

void GraphicObject::setTransformationMatrix(Transform transform){
	this->transformMatrix = transform;
}

Transform GraphicObject::getTransformationMatrix(){
	return Transform(this->transformMatrix);
}

void GraphicObject::setPixel(int x, int y, Color color, unsigned char* frame) {
	if ((x>=0 && y>=0) && (x < width && y < height) ) {
		frame[(y * width + x) * 3 + 0] = color.getR();
		frame[(y * width + x) * 3 + 1] = color.getG();
		frame[(y * width + x) * 3 + 2] = color.getB();
	}
}