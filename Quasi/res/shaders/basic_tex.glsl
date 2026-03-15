// #shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in float texID;
layout(location = 3) in float texCorner;

out vec4 v_color;
out vec2 v_texID;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform iv2 texSize;

void main()
{
    v_color = color;
    // texture order: bottom to top (y), left to right (x), y after x.
    //      id order: top to bottom (y), left to right (x), y after x.
    vec2 texCoord = vec2(int(texID) % texSize.x, texSize.y - 1 - (int(texID) / texSize.x));
    // switch (int(texCorner)) {
    //     case 0: break;
    //     case 1: texCoord += vec2(1, 0); break;
    //     case 2: texCoord += vec2(0, 1); break;
    //     case 3: texCoord += vec2(1, 1); break;
    //     default: break;
    // }
    // above simplified to x = t % 2, y = t / 2
    texCoord += vec2(int(texCorner) % 2, int(texCorner) / 2);
    v_texID = texCoord / vec2(texSize);
    gl_Position = u_projection * u_view * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 gl_Color;

in vec4 v_color;
in vec2 v_texID;

uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, v_texID);
    gl_Color = texColor * v_color;
}