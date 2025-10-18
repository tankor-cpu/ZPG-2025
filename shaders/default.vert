#version 330 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 color;

out vec3 vColor;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main() {
    gl_Position = P * V * M * vec4(vp, 1.0);
    vColor = color;
}
