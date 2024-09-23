#version 330 core
out vec4 FragColor;

uniform vec3 color;
uniform float brightness;

void main()
{
	FragColor = vec4(color * clamp(brightness, 0.0, 1.0), 1.0);
}