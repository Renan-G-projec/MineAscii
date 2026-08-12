#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

out vec2 texCoords;

void main()
{
    gl_Position = camMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    texCoords = aTex;
}