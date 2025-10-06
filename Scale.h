#pragma once
#include "Transformation.h"

class Scale : public Transformation
{
public:
	Scale(const glm::vec3& scales);
	glm::mat4 getMatrix() const override;
private:
	glm::vec3 scales;
};

