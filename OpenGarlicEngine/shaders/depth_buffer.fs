#version 330 core
out vec4 FragColor;

uniform sampler2D depthTexture;

in vec2 TexCoords;

void main()
{
    // Get depth value from depth buffer
    float depthValue = texture(depthTexture, TexCoords).r;
    
    // Visualize depth as grayscale
    FragColor = vec4(vec3(depthValue), 1.0);
}