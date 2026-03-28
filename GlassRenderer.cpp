#include "GlassRenderer.h"

namespace Carpet {
    GlassRenderer::GlassRenderer(GraphicsDevice& gd) : sdfRenderer(gd) {
        glassShader = Shader::NewFragment(R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap, bgPlain, bgGlass;
uniform vec3 lightSource;
uniform vec2 screenSize;
uniform float eta, height, bevelRadius, S;

float lumi(vec3 col) {
    return dot(col, vec3(0.2126, 0.7152, 0.0722));
}
// All components are in the range [0…1], including hue.
vec3 rgb2hsv(vec3 c) {
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}
// All components are in the range [0…1], including hue.
vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
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
    float L = -cos(3.1415926 * dot(h.xy, normalize(lightSource.xy)));
    float lum = lumi(result), light = (0.8 + L) * 0.15;
    float glare = (1 + L) * pow(max(0.001, 1 - h.z * h.z), bevelRadius / 3.0f);
    result *= 0.7 + 0.5 * lum + (0.1 + light) * sqrt(max(0.0001, light) + 0.05) * 1.3 * (4.0 - 2.7 * lum);
    result += hsv2rgb(rgb2hsv(result) * vec3(1.0, 1.0 + 0.32 * glare - 0.6 * lum, 1.2)) * (0.2 * glare / lum);
    glColor = vec4(result, 1.0);
})");

#ifndef NDEBUG
        heightVis = Shader::NewFragment(R"(
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
        )");
#endif
    }

    void GlassRenderer::SetSmoothing(float strength) {
        sdfRenderer.SetSmoothing(strength);
    }

    float GlassRenderer::GetSmoothingStrength() const {
        return sdfRenderer.GetSmoothingStrength();
    }

    void GlassRenderer::SetBevel(float radius) {
        sdfRenderer.bevelRadius = radius;
    }

    float GlassRenderer::GetBevelRadius() const {
        return sdfRenderer.bevelRadius;
    }

    void GlassRenderer::DrawBox(const fRect2D& rect, float r) {
        sdfRenderer.DrawBox(rect, r);
    }

    void GlassRenderer::DrawCirc(const fv2& center, float r) {
        sdfRenderer.DrawCirc(center, r);
    }

    void GlassRenderer::Render() {
        sdfRenderer.Render();

#ifndef NDEBUG
        if (debugHeightmap) {
            heightVis.Bind();
            heightVis.SetUniformArgs({
                { "heightmap",        sdfRenderer.GetHeightmap(), 0 },
                { "bevelRadius",      sdfRenderer.bevelRadius },
                { "showActualHeight", showActualHeight }
            });
            Render::DrawScreenQuad(heightVis);
            return;
        }
#endif

        glassShader.Bind();
        glassShader.SetUniformArgs({
            { "heightmap",   sdfRenderer.GetHeightmap(), 0 },
            { "bgPlain",     background,      1 },
            { "bgGlass",     backgroundGlass, 2 },
            { "lightSource", lightDirection },
            { "screenSize",  (fv2)sdfRenderer.canvasSize },
            { "eta",         eta },
            { "height",      height },
            { "bevelRadius", sdfRenderer.bevelRadius },
            // { "S", S }
        });
        // glassShader.SetUniformFloat("maxZ", renderer.bevelSize);
        Render::DrawScreenQuad(glassShader);
    }
} // Carpet