#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main()
{
    gl_Position = camMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}