#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap;
uniform float extrudeZ;

void main() {
    vec4 h = texture(heightmap, vPosition);
    glColor = vec4(h.xyz * 0.5 + 0.5, h.w / extrudeZ);
}