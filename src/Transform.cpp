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

glm::mat3x3 Transform::rotate (const float degrees, const glm::vec3& axis){
	glm::vec3 axisbuf = glm::normalize(axis);
	float tetha = glm::radians(degrees);
	float aX = axisbuf[0];
	float aY = axisbuf[1];
	float aZ = axisbuf[2];

	glm::mat3x3 first = cos(tetha) * glm::mat3x3(	1,0,0,
													0,1,0,
													0,0,1);

	glm::mat3x3 second = (1-cos(tetha)) * glm::mat3x3(	aX * aX, aX * aY, aX * aZ,
														aX * aY, aY * aY, aY * aZ,
														aX * aZ, aY * aZ, aZ * aZ);
	
	glm::mat3x3 third = sin(tetha) * glm::mat3x3( 0, -aZ,  aY,
													aZ,   0, -aX,
												-aY,  aX,   0);


	glm::mat3x3 rotatedMatrix = first + second + third;

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