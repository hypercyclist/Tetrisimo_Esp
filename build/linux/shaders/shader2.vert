#version 330 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec3 inColor;
out vec3 outColor;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = view * model * 
        vec4(inPosition.x * 2, 
             inPosition.y * 2, 
             0.0f, 
             1.0f);
    outColor = inColor;
}