#include "CombinedTransformation.h"

CombinedTransformation::CombinedTransformation() = default;

CombinedTransformation::~CombinedTransformation()
{
    clear();
}

void CombinedTransformation::addTransformation(Transformation* t)
{
    transformations.push_back(t);
}

glm::mat4 CombinedTransformation::getMatrix() const
{
    glm::mat4 result = glm::mat4(1.0f);

    for (const auto& t : transformations) {
        if (t) {
            result = result * t->getMatrix();
        }
    }

    return result;
}

void CombinedTransformation::clear()
{
    for (auto t : transformations) {
        delete t;
    }
    transformations.clear();
}