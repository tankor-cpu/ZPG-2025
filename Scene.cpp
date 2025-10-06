#include "Scene.h"

void Scene::addObject(SceneObject* ob)
{
	objects.push_back(ob);
}

SceneObject* Scene::getObject(size_t index)
{
	if (index < objects.size()) {
		return objects[index];
	}
	return nullptr;
}


void Scene::draw(const glm::mat4& P, const glm::mat4& V) const
{
	for (auto& obj : objects) {
		obj->draw(P, V);
	}
}

void Scene::clear()
{
	for (auto obj : objects) {
		delete obj;
	}
	objects.clear();
}
