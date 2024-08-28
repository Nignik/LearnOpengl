#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

void main() {
    vec3 col = vec3(0.6, 0.3, 0.3);
    FragColor = vec4(col, 1.0);
}