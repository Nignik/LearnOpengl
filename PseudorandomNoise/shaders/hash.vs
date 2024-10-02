#version 450 core

layout (location = 0) in vec3 aPos;

layout(std430, binding = 0) buffer TransformsBuffer
{
    mat4 transforms[];
};

layout(std430, binding = 1) buffer HashBuffer
{
    uint hashes[];
};

uniform mat4 view;
uniform mat4 projection;

flat out uint hash;

void main() {
    hash = hashes[gl_InstanceID];
    gl_Position = projection * view * transforms[gl_InstanceID] * vec4(aPos, 1.0);
}