#pragma once

#include <glm/glm.hpp>

class Transform{
private:
	glm::mat3x3 matrix;
public:
	enum Mode {TRANSLATE, ROTATE, SCALE};

	Transform();
	Transform(glm::mat3x3 mat);
	glm::vec2 Transform::operator* (glm::vec2 &v);
	Transform Transform::operator* (Transform &t);
	bool operator== (const Transform &other) const;
	bool operator!= (const Transform &other) const;

	static glm::mat3x3 scale(const float &sx, const float &sy);
	static glm::mat3x3 translate (const float &tx, const float &ty);
	static glm::mat3x3 rotate (const float &degrees, const float &dummy);
};