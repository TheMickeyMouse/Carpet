#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 v_color;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
    gl_Position = u_projection * u_view * position;
    v_color = color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;

void main()
{
    color = v_color;
}