#include "Pythagoras.h"


Pythagoras::Pythagoras()
{
	glm::vec2 A, B, C;
	
	this->size = 20;
	int position = 200;
	A = glm::vec2(position, position);
	B = glm::vec2(4 * size + position, position);
	C = glm::vec2(position, 3 * size + position);
	
	glm::vec2 S = glm::vec2 ((A.x + B.x + C.x) / 3.0f, (A.y + B.y + C.y) / 3.0f);

	this->vertices.push_back(A);
	this->vertices.push_back(B);
	this->vertices.push_back(C);
	this->vertices.push_back(S);
	this->isCompleted = false;
}


Pythagoras::~Pythagoras(void)
{
}

GraphicObject* Pythagoras::copy() const{
	return NULL;
}

void Pythagoras::addPoint(int x, int y){
	if (this->isCompleted)
		return;

	glm::vec2 A, B, C;
	A = glm::vec2(x, y);
	B = glm::vec2(4 * size + x, y);
	C = glm::vec2(x, 3 * size + y);

	glm::vec2 S = glm::vec2 ((A.x + B.x + C.x) / 3.0f, (A.y + B.y + C.y) / 3.0f);

	this->vertices.at(0) = A;
	this->vertices.at(1) = B;
	this->vertices.at(2) = C;
	this->vertices.at(3) = S;
	this->isCompleted = true;
}

void Pythagoras::draw(unsigned char* frame){
	if (!this->isCompleted)
		return;

	glm::vec2 A, B, C;
	glm::vec2 AB_outVector, AC_outVector, Hypo_outVector;
	std::vector<Line> lines;

	A = this->vertices.at(0);
	B = this->vertices.at(1);
	C = this->vertices.at(2);

	//this->rAn.push_back(Line(A, B));
	AB_outVector = -glm::normalize(B - A) * 3.0f * this->size;
	lines.push_back(Line(A, A + AB_outVector));
	lines.push_back(Line(C, C + AB_outVector));
	lines.push_back(Line(A + AB_outVector, C + AB_outVector));

	AC_outVector = -glm::normalize(C - A) * 4.0f * this->size;
	lines.push_back(Line(B, B + AC_outVector));
	lines.push_back(Line(A, A + AC_outVector));
	lines.push_back(Line(A + AC_outVector, B + AC_outVector));

	Hypo_outVector =  Transform(Transform::rotate(-90, 0)) * (-glm::normalize(B - C)  * 5.0f * this->size);
	lines.push_back(Line(B, B + Hypo_outVector));
	lines.push_back(Line(C, C + Hypo_outVector));
	lines.push_back(Line(C + Hypo_outVector, B + Hypo_outVector));
	//this->rAn.push_back(Line(t.vertices.at(0), t.vertices.at(1)));

	Triangle2D(A,B,C).draw(frame);
	for (auto p : lines)
		p.draw(frame);

	lines.clear();
}