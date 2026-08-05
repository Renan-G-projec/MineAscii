#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 rot;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) * rot;
}