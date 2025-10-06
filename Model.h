#pragma once
#include <GL/glew.h>
#include <vector>

class Model {
public:
	Model();
	~Model();

	void setVertices(const std::vector<float>& data, int stride, int positionOffset, int colorOffset);
	void draw() const;
private:
	GLuint VBO = 0;
	GLuint VAO = 0;
	GLsizei vertexCount = 0;
	int components_ = 3;
};