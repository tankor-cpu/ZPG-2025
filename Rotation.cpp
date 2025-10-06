#include "Rotation.h"

Rotation::Rotation(float angle, float x, float y, float z)
    : angle(angle), axisX(x), axisY(y), axisZ(z) {}

glm::mat4 Rotation::getMatrix() const
{
    return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(axisX, axisY, axisZ));
}
