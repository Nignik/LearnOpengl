#version 450 core

flat in uint hash;

out vec4 FragColor;

void main() {
    FragColor = vec4(vec3(1.0) * (hash / 256.0), 1.0);
}