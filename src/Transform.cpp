#include <glm/glm.hpp>
#include "Transform.h"

Transform::Transform(){
	this->matrix = glm::mat3x3();
}

Transform::Transform(glm::mat3x3 mat){
	this->matrix = mat;
}

glm::mat3x3 Transform::scale(const float &sx, const float &sy) 
{
	return glm::mat3x3 (sx, 0 , 0,
						0 , sy, 0,
						0 , 0 , 1);
	
}

glm::mat3x3 Transform::translate (const float &tx, const float &ty){
	return glm::mat3x3(	1,0,tx,
						0,1,ty,
						0,0,1);
}

glm::mat3x3 Transform::rotate (const float &degrees, const float &dummy){
	float tetha = glm::radians(degrees);

	glm::mat3x3 rotatedMatrix = glm::mat3x3(cos(tetha), -sin(tetha), 0,
											sin(tetha),  cos(tetha), 0,
													0,0,1);

	// You will change this return call
	return rotatedMatrix;
}

glm::vec2 Transform::operator* (glm::vec2 &v) {
	v.x = this->matrix[0][0] * v.x + this->matrix[0][1] * v.y + this->matrix[0][2] * 1;
	v.y = this->matrix[1][0] * v.x + this->matrix[1][1] * v.y + this->matrix[1][2] * 1;
	return v;
}

Transform Transform::operator* (Transform &t){
	return this->matrix * t.matrix;
}

bool Transform::operator== (const Transform &other) const{
	if (this->matrix == other.matrix)
		return true;
	else
		return false;
}

bool Transform::operator!= (const Transform &other) const{
	return !this->operator==(other);
}