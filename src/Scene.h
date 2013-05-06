#pragma once

#include <vector>
#include <glm\glm.hpp>
#include "GraphicObject.h"

class Scene{
private:
	bool auto_rotation;
	bool local_global_rotation;
	bool show_vertices;
	int frameWidth, frameHeight;
	unsigned char* frame;
	Transform inputTransform;
	GraphicObject* currentGraphicObject;
	GraphicObject::Mode graphicObjectMode;
	Transform::Mode graphicTransformMode;

	std::vector<GraphicObject*> graphicObjects;
	glm::vec2 pivotPoint;

public:
	Scene(int frameWidth, int frameHeight);
	
	void add(GraphicObject* graphicObject);
	GraphicObject* getCurrentGraphicObject();
	std::vector<GraphicObject*> getAllGraphicObjects();
	glm::vec2* selectGraphicObjectAt(int x, int y);

	GraphicObject::Mode getGraphicObjectMode();
	void setCurrentGraphicObjectMode(GraphicObject::Mode mode);

	Transform::Mode getGraphicTransformMode();
	void setGraphicTransformtMode(Transform::Mode mode);

	Transform getInputTransform();
	void setInputTransform(Transform t);

	void drawAllGraphicObjects();
	void drawGraphicObject(GraphicObject* graphicObject);
	void clearGraphicObjects();

	void toggleShowVertices();
	bool getShowVertices();

	void toggleAutoRotation();
	bool getAutoRotation();

	void toggleLocalGlobalRotation();
	bool getLocalGlobalRotation();

	unsigned char* getFrame();
	void setFrame(unsigned char* newframe);
	void clearFrame();

	int getFrameHeight(){ return this->frameHeight;}
	int getFrameWidth(){ return this->frameWidth;}
	
	void loadFrame(char* location);
	void saveFrame(char* location);
};