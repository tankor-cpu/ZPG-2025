#pragma once
#include "Transformation.h"

class Translation : public Transformation
{
public:
	Translation(const glm::vec3& offset);

	glm::mat4 getMatrix() const override;

private:
	glm::vec3 offset;
};

