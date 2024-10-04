#version 450 core

flat in uint hash;

out vec4 FragColor;

void main() {
    vec3 hashColor = (1.0 / 255.0) * vec3(
        hash & 255,
        (hash >> 8) & 255,
        (hash >> 16) & 255);

    FragColor = vec4(hashColor, 1.0);
}