#pragma once

namespace Carpet::Shaders {
#pragma region SDFs
    // language=GLSL
    static constexpr const char* SDFCalcVert =
R"(
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec2 rs;
layout (location = 3) in int prim;
out vec4 vUVs;
flat out int vPrim;
uniform vec2 screenSize;

void main() {
   gl_Position = vec4(position * 2 / screenSize - 1.0, 1.0, 1.0);
   vUVs = vec4(uv, rs);
   vPrim = prim;
}
)";

    // language=GLSL
    static constexpr const char* SDFCalcFrag =
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec4 vUVs;
flat in int vPrim;
uniform float strength, bevelRadius;
uniform sampler2D fontSDF;

// returns gradient + distance
vec3 sdfCirc(vec2 p, float r, float t) {
    float l = length(p);
    return vec3(p / l, l * r - t);
}
vec3 sdfTex(vec2 coords, float r, float t) {
    float h = (max(-texture(fontSDF, coords).r + 0.5, -t) - t) * r;
    // smoother version:
    // vec2 dx = dFdx(coords), dy = dFdy(coords);
    // vec2 grad = vec2(texture(fontSDF, coords - dx).r - texture(fontSDF, coords + dx).r,
    //                  texture(fontSDF, coords - dy).r - texture(fontSDF, coords + dy).r);
    vec2 grad = vec2(dFdx(h), dFdy(h));
    return vec3(grad, h);
}
vec3 SDF(vec4 uv, int prim) {
    switch (prim) {
        case 0: return sdfCirc(2 * uv.xy - 1, uv.z, uv.w);
        case 1: return vec3(0, 0, uv.z);
        case 2: return sdfTex(uv.xy, uv.z, uv.w);
        default: return vec3(0);
    }
}

void main() {
    vec3 sdf = SDF(vUVs, vPrim);
    float s = exp(min(-sdf.z / strength, bevelRadius));
    glColor = vec4(sdf.xy * s, s, -sdf.z);
})";
#pragma endregion

#pragma region Height Calculation
    /*
     * calculating new gradient:
     * given H(x, y) = h(g(f(x, y))) where f: R^3 -> R, g(x) = -ln(x) * strength
     * then grad H = grad (g comp f) * h'(g comp f)
     *             = (grad f * g'(f)) * h'(g comp f)
     * if d = f(x, y) and G = grad f(x, y), z = -ln(d) * s, and h'(x) = p(x)/q(x)
     * then grad H = G * g'(d) * h'(g(d))
     *             = G * -s/d * h'(-ln(x) * s);
     *             = (N * p(z)) / (d * q(z))
     *             (we can set G * s = N because in the render shader we store N instead of G)
     *       and H = h(-ln(x) * s) = h(z);
     *
     *       which means we control p(z), q(z) and h(z) to our needs.
     */

    /*  useful h functions:
     *  (to find one, first use a simple function, take its derivative and separate the numerator and denom.)
     *  return value is in (p, q, h) where p/q = h' and h is the actual result
     *
     *  - circular:
     *      vec3 height(float z) {
     *          z = clamp(z, 0, bevelRadius);
     *          float H = sqrt((2 * bevelRadius - z) * z);
     *          return vec3(bevelRadius - H, H, H);
     *      }
     *      // pros: simple, cons: non C2 continuous, lighting artefacts may appear
     *  - squricle:
     *      vec3 height(float z) {
     *          z = 1 - clamp(z / bevelRadius, 0, 1);
     *          float z3 = z * z * z, H4 = 1 - z3 * z, H = sqrt(sqrt(H4));
     *          return vec3(z3 * H, H4, bevelRadius * H);
     *      }
     *      // pros: C2 continuous, cons: slow
     */

    // also returns SDF in the alpha channel when negative :)
    // -inf means too far away from any nearby objects

    // language=GLSL
    static constexpr const char* HeightCalcFrag =
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D disGraMap;
uniform float bevelRadius, strength;

// returns h' in form of p/q, and h itself
vec3 height(float z) {
    z = 1 - clamp(z / bevelRadius, 0, 1);
    float z3 = z * z * z, H4 = 1 - z3 * z, H = sqrt(sqrt(H4));
    return vec3(z3 * H, H4, bevelRadius * H);
}

void main() {
    // !! DO NOT CHANGE THIS PART (expect height(z)) !!
    vec3 d_gra = texture(disGraMap, vPosition).xyz;
    float d = d_gra.z, z = log(d) * strength;
    vec3 h = height(z);
    vec3 n = vec3(d_gra.xy * h.x, d * h.y);
    glColor = vec4(normalize(n), z > 0.0 ? h.z : z);
}
)";
#pragma endregion

#pragma region Glass Optics
    // language=GLSL
    static constexpr const char* GlassFrag =
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap, bgPlain, bgGlass;
uniform vec3 lightSource;
uniform vec2 screenSize;
uniform float eta, height, bevelRadius;
uniform vec4 glassTint;
uniform float dropShadowRadius, dropShadowPow;
uniform float mainShadowDist, mainShadowPow;

float lumi(vec3 col) {
    return dot(col, vec3(0.2126, 0.7152, 0.0722));
}
vec3 saturate(vec3 color, float dS) {
	float M = max(color.r, max(color.g, color.b));
	vec3 p = color - M;
	float m = min(p.r, min(p.g, p.b));
	// you *could* remove the '- 1e-6' and 'clamp', but not recommended
	p *= dS / (m - 1e-6);
	return clamp(color - M * p, 0, M);
}
vec3 scaleSat(vec3 color, float kS) {
    float M = max(color.r, max(color.g, color.b));
    return mix(vec3(M), color, kS);
}
float sq(float x) { return x * x; }

void main() {
    vec4 h = texture(heightmap, vPosition);
    if (h.w <= 0.0) {
        vec3 result = texture(bgPlain, vPosition).rgb;

        float shadow = 0.94;
        float w = max(texture(heightmap, vPosition + lightSource.xy * mainShadowDist / screenSize).w / bevelRadius, 0);
        shadow *= 1 - smoothstep(0, 1, 0.4 * w * w) * mainShadowPow;
        shadow *= 1 - smoothstep(-1, 0, h.w / dropShadowRadius) * dropShadowPow;

        glColor = vec4(result * shadow, 1.0);
        return;
    }

    vec3 pos = vec3(vPosition * screenSize, h.w);
    pos.xy /= screenSize;
    pos.z += height;

    vec3 dirR = refract(vec3(0, 0, -1), h.xyz, eta * 1.15),
         dirG = refract(vec3(0, 0, -1), h.xyz, eta),
         dirB = refract(vec3(0, 0, -1), h.xyz, eta * 0.87);

    vec3 result = vec3(
        texture(bgGlass, pos.xy - dirR.xy / screenSize * (pos.z / dirR.z)).r,
        texture(bgGlass, pos.xy - dirG.xy / screenSize * (pos.z / dirG.z)).g,
        texture(bgGlass, pos.xy - dirB.xy / screenSize * (pos.z / dirB.z)).b
    );

    result = result * mix(vec3(1), glassTint.rgb, glassTint.a);

    float L = -cos(3.1415926 * dot(h.xy, normalize(lightSource.xy)));
    float lum = lumi(result), light = (0.8 + L) * 0.2, invlum = 1 / sqrt(lum + 0.01);
    float glare = (0.8 + L) * pow(max(0.001, 1 - h.z * h.z), bevelRadius / 3.0f);

    result *= 1.04 + light * invlum;
    result = saturate(result, 0.05);
    result += (0.25 * glare * invlum) * scaleSat(result, 0.4);

    glColor = vec4(result, 1.0);
}
)";
#pragma endregion

#pragma region Gaussian Blur
    // check out https://www.rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
    // language=GLSL
    static constexpr const char* GaussBlurXFrag =
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D image;

void main(void) {
    const float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
    const float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);

    glColor = texture2D(image, vPosition) * weight[0];
    for (int i = 1; i < 3; i++) {
        vec2 xOff = vec2(offset[i] / textureSize(image, 0).x, 0);
        glColor += texture2D(image, vPosition + xOff) * weight[i];
        glColor += texture2D(image, vPosition - xOff) * weight[i];
    }
}
)";
    // language=GLSL
    static constexpr const char* GaussBlurYFrag =
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D image;

void main(void) {
    const float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
    const float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);

    glColor = texture2D(image, vPosition) * weight[0];
    for (int i = 1; i < 3; i++) {
        vec2 xOff = vec2(0, offset[i] / textureSize(image, 0).y);
        glColor += texture2D(image, vPosition + xOff) * weight[i];
        glColor += texture2D(image, vPosition - xOff) * weight[i];
    }
}
)";
#pragma endregion

#pragma region Debugging
    // language=GLSL
    static constexpr const char* HeightDebugFrag =
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap;
uniform float bevelRadius;
uniform int showActualHeight;

void main() {
    vec4 h = texture(heightmap, vPosition);
    glColor = h.w == 0 ? vec4(0.0) : showActualHeight == 1 ? vec4(h.w / bevelRadius) : vec4(h.xyz * 0.5 + 0.5, h.w / bevelRadius);
}
)";
#pragma endregion
}