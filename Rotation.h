#pragma once
#include "Transformation.h"

class Rotation : public Transformation
{
public:
	Rotation(float angle, float x, float y, float z);
	glm::mat4 getMatrix() const override;
private:
	float angle;
	float axisX, axisY, axisZ;
};

