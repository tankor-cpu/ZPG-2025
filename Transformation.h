#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale

class Transformation {
public:
	virtual ~Transformation() = default;
	virtual glm::mat4 getMatrix() const = 0;
	
};