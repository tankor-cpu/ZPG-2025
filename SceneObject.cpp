#include "SceneObject.h"

SceneObject::SceneObject(Model* model, ShaderProgram* shaderProgram, Transformation* transformation)
	: model(model), shaderProgram(shaderProgram), transformation(transformation)
{
}

void SceneObject::draw(const glm::mat4& P, const glm::mat4& V)
{
	glm::mat4 PVM = P * V * transformation->getMatrix();
	shaderProgram->use();
	shaderProgram->setUniform("PVM", PVM);

	model->draw();
}

void SceneObject::setTransformation(Transformation* transformation)
{
	this->transformation = transformation;
}

SceneObject::~SceneObject()
{
	delete transformation;
}
