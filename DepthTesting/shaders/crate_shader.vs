#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 scale = vec3(model[0][0], model[1][1], model[2][2]);
    TexCoords = aTexCoords * scale.xy;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}