#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 7) in mat4 transform;

layout(std430, binding = 0) buffer HashBuffer
{
    uint hashes[];
};

uniform mat4 view;
uniform mat4 projection;

flat out uint hash;

void main() {
    hash = hashes[gl_InstanceID];
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
}