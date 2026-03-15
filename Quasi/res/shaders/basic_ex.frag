#version 330 core

layout(location = 0) out vec4 glColor;

in vec4 v_color;
flat in int v_texID;
flat in int v_texCorner;

uniform sampler2D tex;
uniform iv2 texSize;

void main()
{
    vec2 texCoord = vec2(v_texID % texSize.x, v_texID / texSize.x);
    if (v_texCorner == 1) {
        texCoord += vec2(1, 0);
    } else if (v_texCorner == 2) {
        texCoord += vec2(1, 1);
    } else if (v_texCorner == 3) {
        texCoord += vec2(0, 1);
    }
    texCoord = texCoord / vec2(texSize);
    vec4 texColor = texture(tex, texCoord);
    glColor = v_color * texColor;
}