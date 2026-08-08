#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 camMatrix;

out vec2 texCoords;

void main()
{
    gl_Position = camMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    texCoords = aTex;
}