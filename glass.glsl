#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap, bgPlain, bgGlass;
uniform vec3 lightSource;
uniform vec2 screenSize;
uniform float eta, height;

bool castRay(in vec3 origin, in vec3 dir, out float resT) {
    float dt = 0.01;
    float mint = 0.01;
    float maxt = 160.0;
    float lh = 0.0;
    float ly = 0.0;
    for (float t = mint; t < maxt; t += dt)  {
        vec3  p = origin + dir * t;
        float h = -texture(heightmap, p.xy).w;
        if (p.z < h) {
            // interpolate intersection distance
            resT = t-dt+dt*(lh-ly)/(p.y-ly-h+lh);
            return true;
        }
        // accuracy proportional to the distance
        lh = h;
        ly = p.z;
        dt = 0.05 * t;
    }
    return false;
}

float pow4(float x) {
    x = x * x;
    return x * x;
}

void main() {
    vec4 h = texture(heightmap, vPosition);
    if (h.w < 0.001) {
        glColor = texture(bgPlain, vPosition);
        return;
    }
    vec3 pos = vec3(vPosition * screenSize, h.w);
    vec3 n = normalize(h.xyz);
    vec3 dir = refract(vec3(0, 0, -1), n, eta);

    float raylen = 0.0;
    bool hasHit = castRay(pos / vec3(screenSize, 1.0), dir / vec3(screenSize, 1.0), raylen);
    if (!hasHit) {
        glColor = vec4(1.0, 0.0, 1.0, 1.0);
        return;
    }
    vec3 hit = pos + raylen * dir;

    // glColor = vec4(hit, 1.0);
    vec3 normal = normalize(texture(heightmap, hit.xy / screenSize).xyz * vec3(-1.0, -1.0, 1.0));
    vec3 escapeDir = refract(dir, normal, 1.0 / eta);
    vec2 screenHit = hit.xy + escapeDir.xy * (hit.z + height);
    // glColor = vec4(screenHit, 0.0, 1.0);
    vec3 result = texture(bgGlass, screenHit / screenSize).xyz;
    result *= 0.85 + pow4(dot(normalize(lightSource - pos), n));
    glColor = vec4(result, 1.0);
}