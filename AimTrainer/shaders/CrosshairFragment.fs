#version 330 core

in vec2 fragCoord;

out vec4 outColor;

uniform vec4 color;

void main() {
    vec2 uv = fragCoord;
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(uv, center);

    if (dist <= 0.002) {
        outColor = vec4(0.0, 0.5, 0.5, 1.0);
    }
    else {
        outColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
}