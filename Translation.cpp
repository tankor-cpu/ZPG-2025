#include "Translation.h"

Translation::Translation(const glm::vec3& offset) : offset(offset)
{}

glm::mat4 Translation::getMatrix() const
{
	return glm::translate(glm::mat4(1.0f), offset);
}
