#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap;
uniform float bevelRadius;
uniform int showActualHeight;

void main() {
    vec4 h = texture(heightmap, vPosition);
    glColor = h.w == 0 ?
                vec4(0.0) :
                showActualHeight == 1 ?
                    vec4(h.w / bevelRadius) :
                    vec4(h.xyz * 0.5 + 0.5, h.w / bevelRadius);
}