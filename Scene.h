#pragma once
#include "SceneObject.h"
#include <vector>

class Scene
{
public:
	void addObject(SceneObject* object);
	SceneObject* getObject(size_t index);

	void draw(const glm::mat4& P, const glm::mat4& V) const;
	void clear();
private:
	std::vector<SceneObject*> objects;
};

