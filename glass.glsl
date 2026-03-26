#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap, bgPlain, bgGlass;
uniform vec3 lightSource;
uniform vec2 screenSize;
uniform float eta, height;

bool castRay(in vec3 origin, in vec3 dir, out float resT) {
    // future, better method
    // goal: finding intersection of
    // h(x) = -texture(heightmap, p.xy / screenSize).w;
    // f(x) = (mx + b) / f0;
    // equivalent to finding root of f0 * h(x) - (mx + b)

    float dt = 0.95 + 0.05 * 0.05 / 1.05;
    float mint = 1.0;
    float maxt = 300.0;
    float lh = 0.0;
    float ly = 0.0;

//    float tryLen = origin.z / -dir.z;
//    vec3 tryOrigin = origin + tryLen * dir;
//    bool outOfBounds = texture(heightmap, tryOrigin.xy / screenSize).w == 0.0;
//    tryOrigin = outOfBounds ? origin : tryOrigin;
//    float s = outOfBounds ? 1 : -1;
//    resT = outOfBounds ? 0.0 : tryLen;

    for (float t = mint; t < maxt; t += dt)  {
        vec3  p = origin + dir * t;
        float h = -texture(heightmap, p.xy / screenSize).w;
        if (p.z < h) {
            // interpolate intersection distance
            resT = t - dt + dt * (lh - ly) / (p.z - ly - h + lh);
            return true;
        }
        lh = h;
        ly = p.z;
        // accuracy proportional to the distance
        dt = 0.95 + 0.05 * t;
    }
    return false;
}

float pow4(float x) {
    x = x * x;
    return x * x;
}

void main() {
    vec4 h = texture(heightmap, vPosition);
    if (h.w < 0.01) {
        glColor = texture(bgPlain, vPosition);
        return;
    }
    vec3 pos = vec3(vPosition * screenSize, h.w);
    vec3 dir = refract(vec3(0, 0, -1), h.xyz, eta);

    float raylen = pos.z / -dir.z;
    float l = 0.0;
    bool hasHit = castRay(pos + dir * raylen, dir, l);
    if (!hasHit) {
        glColor = vec4(1.0, 0.0, 1.0, 1.0);
        return;
    }
    vec3 hit = pos + (raylen + l) * dir;

    // glColor = vec4(hit, 1.0);
    vec3 escapeN = texture(heightmap, hit.xy / screenSize).xyz * vec3(-1.0, -1.0, 1.0);
    vec3 escapeDir = refract(dir, escapeN, 1.0 / eta);
    vec2 screenHit = hit.xy + escapeDir.xy * ((hit.z + height) / -escapeDir.z);
    glColor = vec4((raylen + l) / 120.0, 0.0, 0.0, texture(bgGlass, screenHit / screenSize).w + lightSource.x);
    // glColor = vec4(screenHit, 0.0, 1.0);
//    vec3 result = texture(bgGlass, screenHit / screenSize).xyz;
//    result *= 1.0 + pow4(dot(lightSource, h.xyz));
//    glColor = vec4(result, 1.0);
}