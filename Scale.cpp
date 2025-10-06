#include "Scale.h"

Scale::Scale(const glm::vec3& scales) : scales(scales)
{}

glm::mat4 Scale::getMatrix() const
{
	return glm::scale(glm::mat4(1.0f), scales);
}
