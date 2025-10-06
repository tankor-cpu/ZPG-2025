#version 330 core
layout(location=0) in vec3 vp;
layout(location = 1) in vec3 color;

out vec3 vColor;

uniform mat4 PVM;

void main() {
    gl_Position = PVM * vec4 (vp, 1.0);
    vColor = color;
}
