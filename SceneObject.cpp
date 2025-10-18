#include "SceneObject.h"

SceneObject::SceneObject(Model* model, ShaderProgram* shaderProgram, Transformation* transformation)
	: model(model), shaderProgram(shaderProgram), transformation(transformation)
{
}

void SceneObject::draw(const glm::mat4& P, const glm::mat4& V)
{
	glm::mat4 M = transformation->getMatrix();
	shaderProgram->use();
	shaderProgram->setUniform("P", P);
	shaderProgram->setUniform("V", V);
	shaderProgram->setUniform("M", M);

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
