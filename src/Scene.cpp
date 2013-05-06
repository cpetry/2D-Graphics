
class Spline;
#include "Scene.h"
#include "Transform.h"
#include "gl/glew.h"
#include "Files/PPMFile.h"
#include "Splines/Line.h"
#include "Splines/Circle.h"
#include "Splines/BezierCurve.h"
#include "Splines/BSpline.h"
#include "Primitives2D/Triangle2D.h"
#include "Primitives2D/Rectangle2D.h"
#include "Primitives2D/Polygon2D.h"
#include "Primitives2D/Pythagoras.h"


Scene::Scene(int frameWidth, int frameHeight)
{
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->frame = new unsigned char[frameWidth * frameHeight * 3];

	this->graphicObjects = std::vector<GraphicObject*>();
	this->graphicObjectMode = GraphicObject::Mode::LINE;
	this->graphicTransformMode = Transform::Mode::TRANSLATE;
	this->currentGraphicObject = NULL;
	this->inputTransform = Transform();

	this->pivotPoint = glm::vec2(frameWidth/2, frameHeight/2);
	this->show_vertices = true;
	this->auto_rotation = false;
}

void Scene::add(GraphicObject* graphicObject)
{
	bool alreadyExists = false;

	for (auto go = this->graphicObjects.begin(); go != this->graphicObjects.end(); go++)
		if (graphicObject == *go)
			alreadyExists = true;

	if (!alreadyExists)
		this->graphicObjects.push_back(graphicObject);
}

GraphicObject* Scene::getCurrentGraphicObject(){
	if (this->currentGraphicObject == NULL
	 || this->currentGraphicObject->isCompleted){
		GraphicObject* go;
		switch (this->graphicObjectMode){
			case GraphicObject::Mode::LINE:{
				go = new Line();
				break;
			}
			case GraphicObject::Mode::CIRCLE:{
				go = new Circle();
				break;
			}
			case GraphicObject::Mode::BEZIER:{
				go = new BezierCurve();
				break;
			}
			case GraphicObject::Mode::BSPLINE:{
				go = new BSpline();
				break;
			}
			case GraphicObject::Mode::TRIANGLE:{
				go = new Triangle2D();
				break;
			}
			case GraphicObject::Mode::RECTANGLE:{
				go = new Rectangle2D();
				break;
			}
			case GraphicObject::Mode::POLYGON:{
				go = new Polygon2D();
				break;
			}
			case GraphicObject::Mode::PYTHAGORAS:{
				go = new Pythagoras();
				break;
			}
			default:{
				go = NULL;
				break;
			}
		}
		currentGraphicObject = go;
	}
	return this->currentGraphicObject;
}

std::vector<GraphicObject*> Scene::getAllGraphicObjects(){
	return this->graphicObjects;
}

glm::vec2* Scene::selectGraphicObjectAt(int x, int y){
	int click_distance = 5;
	if (this->pivotPoint.x > x - click_distance && this->pivotPoint.x < x + click_distance
		&& this->pivotPoint.y > y - click_distance && this->pivotPoint.y < y + click_distance)
		return &this->pivotPoint;
	for (auto& go : this->graphicObjects)
		for (auto& v : go->vertices)
			if ((v.x > x - click_distance && v.x < x + click_distance)
				&& (v.y > y - click_distance && v.y < y + click_distance))
				return &v;
}


GraphicObject::Mode Scene::getGraphicObjectMode(){
	return this->graphicObjectMode;
}

void Scene::setCurrentGraphicObjectMode(GraphicObject::Mode mode){
	this->currentGraphicObject->isCompleted = true;
	this->graphicObjectMode = mode;
}

void Scene::drawAllGraphicObjects()
{
	for (auto graphic : graphicObjects){
		Transform toWorld, transObj, toObject;
		
		//transObj = graphic->getTransformationMatrix();
		
		if (this->auto_rotation)
			transObj = Transform(Transform::rotate(1,0));
		// only if a transformation per input is given
		if (this->getInputTransform() != Transform())
			transObj = this->getInputTransform() * transObj;
		graphic->setTransformationMatrix(transObj);

		//GraphicObject* go = graphic->copy();


		//choosing pivot
		glm::vec2 pivot;
		if (this->getLocalGlobalRotation())
			pivot = graphic->getPivot();
		else
			pivot = this->pivotPoint;

		////////
		// Translate objects to world coordinates
		//toWorld = Transform(glm::mat3x3(1,0,-this->pivotPoint.x,0,1,-this->pivotPoint.y,0,0,1));
		toWorld = Transform(glm::mat3x3(1,0,-pivot.x,0,1,-pivot.y,0,0,1));
		graphic = *graphic * toWorld;
		
		////////
		// Transform all objects
		transObj = graphic->getTransformationMatrix() * transObj;
		graphic = *graphic * transObj;

		////////
		// Translate objects back to their coordinates
		//toObject = Transform(glm::mat3x3(1,0,this->pivotPoint.x,0,1,this->pivotPoint.y,0,0,1));
		toObject = Transform(glm::mat3x3(1,0,pivot.x,0,1,pivot.y,0,0,1));
		graphic = *graphic * toObject;

		drawGraphicObject(graphic);
	}

	// resetting input transformation
	this->setInputTransform(Transform());
}

void Scene::drawGraphicObject(GraphicObject* graphicObject)
{
	Circle c;

	graphicObject->draw(this->frame);
	
	if (this->show_vertices){
		Circle(this->pivotPoint, 5, Color(180,180,100)).draw(this->frame);
		
		for (int i = 0; i < graphicObject->vertices.size(); i++){
			Circle(graphicObject->vertices.at(i), 4, Color(120,120,0)).draw(this->frame);
		}
	}
}

unsigned char* Scene::getFrame()
{
	return this->frame;
}

void Scene::clearGraphicObjects(){
	graphicObjects.clear();
	this->clearFrame();
}

void Scene::clearFrame(){
	for (int i=0; i < this->frameWidth * this->frameHeight * 3; i++) 
		this->frame[i] = 0;
}

void Scene::setFrame(unsigned char* newframe)
{
	this->frame = newframe;
}

void Scene::saveFrame(char* location)
{
	PPMFile::savePPM(location, this->frame, this->frameWidth, this->frameHeight);
}

void Scene::loadFrame(char* location)
{
	PPMFile::readPPM(fopen( location, "r"), new GLsizei(this->frameWidth), new GLsizei(this->frameHeight));
}


Transform Scene::getInputTransform(){
	return this->inputTransform;
}

void Scene::setInputTransform(Transform t){
	this->inputTransform = t;
}

Transform::Mode Scene::getGraphicTransformMode(){
	return this->graphicTransformMode;
}
void Scene::setGraphicTransformtMode(Transform::Mode mode){
	this->graphicTransformMode = mode;
}

void Scene::toggleShowVertices(){
	this->show_vertices = !this->show_vertices;
}

bool Scene::getShowVertices(){
	return this->show_vertices;
}

void Scene::toggleAutoRotation(){
	this->auto_rotation = !this->auto_rotation;
}

bool Scene::getAutoRotation(){
	return this->auto_rotation;
}

void Scene::toggleLocalGlobalRotation(){
	this->local_global_rotation = !this->local_global_rotation;
}

bool Scene::getLocalGlobalRotation(){
	return this->local_global_rotation;
}

void Scene::toggleShowGUI(){
	this->showGUI = !this->showGUI;
}

bool Scene::getShowGUI(){
	return this->showGUI;
}