#pragma once
#include "Transformation.h"
#include <vector>
#include <memory>

class CombinedTransformation : public Transformation
{
public:
    CombinedTransformation();
    ~CombinedTransformation();

    void addTransformation(Transformation* t);

    glm::mat4 getMatrix() const override;
    void clear();
private:
	std::vector<Transformation*> transformations;
};

