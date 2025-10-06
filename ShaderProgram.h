#pragma once
#include <GL/glew.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <string>

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	void use() const;
	bool compileFromSource(const char* vertexSrc, const char* fragmentSrc);
	bool compileFromFile(const char* vertexPath, const char* fragmentPath);

	void setUniform(const std::string& name, const glm::mat4& matrix);
	void setUniform(const std::string& name, const glm::vec3& value);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, int value);
	void setUniform(const std::string& name, bool value);

private:
	GLuint id;
	bool compileShader(GLuint shader,const char* src, const char* tag);
	bool linkProgram(GLuint vs, GLuint fs);
};