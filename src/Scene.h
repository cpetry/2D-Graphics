#include <vector>
#include "GraphicObject.h"

class Scene{
private:
	int frameWidth, frameHeight;
	unsigned char* frame;
	GraphicObject* currentGraphicObject;
	GraphicObject::Mode graphicObjectMode;
	std::vector<GraphicObject*> graphicObjects;

public:
	Scene(int frameWidth, int frameHeight);
	
	void add(GraphicObject* graphicObject);
	GraphicObject* getCurrentGraphicObject();

	void drawAllGraphicObjects();
	void drawGraphicObject(GraphicObject* graphicObject);

	unsigned char* getFrame();
	void setFrame(unsigned char* newframe);
	void clearFrame();

	int getFrameHeight(){ return this->frameHeight;}
	int getFrameWidth(){ return this->frameWidth;}
	
	void loadFrame(char* location);
	void saveFrame(char* location);
};