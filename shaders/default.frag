#version 330 core

in vec3 vColor;
out vec4 fragColor;

uniform vec3 cameraPos;

void main() {
    fragColor = vec4 (vColor, 1.0); 
}
