#version 330 core

uniform float hash;

out vec4 FragColor;

void main() {
    FragColor = vec4(vec3(1.0) * hash, 1.0);
}