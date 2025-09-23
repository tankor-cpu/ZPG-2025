//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

float points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";



const char* fragment_shader =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

