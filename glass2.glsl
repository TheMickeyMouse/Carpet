#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap, bgPlain, bgGlass;
uniform vec3 lightSource;
uniform vec2 screenSize;
uniform float eta, height, bevelRadius;

float lighting(vec2 n, vec2 l) {
    float x = dot(n, l);
    return (0.8 - cos(3.1415927 * x)) * 0.35;
}

float pow8(float x) {
    x *= x;
    x *= x;
    return x * x;
}

void main() {
    vec4 h = texture(heightmap, vPosition);
    if (h.w == 0.0) {
        vec3 result = texture(bgPlain, vPosition).rgb;

        float w = texture(heightmap, vPosition + lightSource.xy / screenSize * (bevelRadius / lightSource.z)).w / bevelRadius;
        const float gamma = 2.2;
        result = pow(pow(result, vec3(1 / gamma)) - 0.5 * smoothstep(0, 1, 0.4 * w * w), vec3(gamma));

        glColor = vec4(result, 1.0);
        return;
    }

    vec3 pos = vec3(vPosition * screenSize, h.w);
    vec3 dir = refract(vec3(0, 0, -1), h.xyz, eta);

    float raylen = (pos.z + height) / -dir.z;
    vec3 hit = pos + raylen * dir;

    vec3 result = texture(bgGlass, hit.xy / screenSize).xyz;
    // normal reflection + fresnel
    float reflStrength = 0.15 * max(reflect(vec3(0, 0, -1), h.xyz).z, 0.0) + 2 * pow8(1 - h.z * h.z);
    result *= 0.85 + lighting(h.xy, normalize(lightSource.xy)) + reflStrength;
    glColor = vec4(result, 1.0);
}