#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


class Shader
{
public:
    Shader() : id(0), type(0) {}
    ~Shader() {
        if (id) { glDeleteShader(id); id = 0; }
    }

    bool loadFromFile(GLenum shaderType, const std::string& path) {
        type = shaderType;

        std::ifstream f(path);
        if (!f) {
            std::cerr << "Failed to open shader file: " << path << "\n";
            return false;
        }
        std::stringstream ss; ss << f.rdbuf();
        std::string src = ss.str();
        const char* csrc = src.c_str();

        id = glCreateShader(type);
        if (!id) {
            std::cerr << "glCreateShader failed (no GL context or GLEW not inited?)\n";
            return false;
        }

        glShaderSource(id, 1, &csrc, nullptr);
        glCompileShader(id);

        GLint ok = GL_FALSE;
        glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char log[2048];
            glGetShaderInfoLog(id, 2048, nullptr, log);
            std::cerr << "Shader compile error (" << path << "):\n" << log << "\n";
            glDeleteShader(id);
            id = 0;
            return false;
        }
        return true;
    }

    friend class ShaderProgram;

private:
    GLuint id;
    GLenum type;
};

