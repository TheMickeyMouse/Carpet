#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in int texID;
layout(location = 3) in int texCorner;

out vec4 v_color;
flat out int v_texID;
flat out int v_texCorner;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_color = color;
    v_texID = texID;
    v_texCorner = texCorner;
}