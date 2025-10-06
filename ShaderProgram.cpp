#include <iostream>
#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>



ShaderProgram::ShaderProgram(){}

ShaderProgram::~ShaderProgram()
{
	if (id != 0) glDeleteProgram(id);
}

void ShaderProgram::use() const
{
	glUseProgram(id);
}

bool ShaderProgram::compileShader(GLuint shader, const char* src, const char* tag)
{
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	GLint ok = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		char log[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, log);
		std::cerr << tag << " compile error:\n" << log << std::endl;
		return false;
	}
	return true;
}

bool ShaderProgram::linkProgram(GLuint vs, GLuint fs)
{
	id = glCreateProgram();
	glAttachShader(id, fs);
	glAttachShader(id, vs);
	glLinkProgram(id);
	GLint ok = GL_FALSE;
	glGetProgramiv(id, GL_LINK_STATUS, &ok);
	if (!ok) {
		char log[1024];
		glGetProgramInfoLog(id, 1024, nullptr, log);
		std::cerr << "program link error:\n" << log << std::endl;
		glDeleteProgram(id);
		id = 0;
		return false;
	}
	glDetachShader(id, fs);
	glDetachShader(id, vs);
	return true;
}



bool ShaderProgram::compileFromSource(const char* vertexSrc, const char* fragmentSrc)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (!compileShader(vertexShader, vertexSrc, "VERTEX")) {
		glDeleteShader(vertexShader);
		return false;
	}
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!compileShader(fragmentShader, fragmentSrc, "FRAGMENT")) {
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return false;
	}

	bool ok = linkProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return ok;

}

bool ShaderProgram::compileFromFile(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vfile(vertexPath); 
	if (!vfile) { 
		std::cerr << "Failed to open: " << vertexPath << "\n"; return false; 
	} 
	std::stringstream vbuf;
	vbuf << vfile.rdbuf();
	std::string vsrc = vbuf.str();
	std::ifstream ffile(fragmentPath);
	if (!ffile) { 
		std::cerr << "Failed to open: " << fragmentPath << "\n"; return false; 
	}
	std::stringstream fbuf;
	fbuf << ffile.rdbuf();
	std::string fsrc = fbuf.str();  
	return compileFromSource(vsrc.c_str(), fsrc.c_str());
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());

	if (location == -1) {
		std::cerr << "Warning: uniform '" << name << "' not found in shader!\n";
		return;	
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());

	if (location == -1) {
		std::cerr << "Warning: uniform '" << name << "' not found in shader!\n";
		return;
	}
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());

	if (location == -1) {
		std::cerr << "Warning: uniform '" << name << "' not found in shader!\n";
		return;
	}
	glUniform1f(location, value);
}

void ShaderProgram::setUniform(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());

	if (location == -1) {
		std::cerr << "Warning: uniform '" << name << "' not found in shader!\n";
		return;
	}
	glUniform1i(location, value);

}

void ShaderProgram::setUniform(const std::string& name, bool value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());

	if (location == -1) {
		std::cerr << "Warning: uniform '" << name << "' not found in shader!\n";
		return;
	}
	glUniform1i(location, value ? 1 : 0);
}


