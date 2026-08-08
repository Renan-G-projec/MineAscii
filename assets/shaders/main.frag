#version 460 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, texCoords);
} 