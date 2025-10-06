#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class SceneObject
{
public:
	SceneObject(Model* model,
		ShaderProgram* shaderProgram,
		Transformation* transformation);

	void draw(const glm::mat4& P, const glm::mat4& V);
	void setTransformation(Transformation* transformation);

	~SceneObject();

private:
	Model* model;
	ShaderProgram* shaderProgram;
	Transformation* transformation;
};

