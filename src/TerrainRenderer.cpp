#include "TerrainRenderer.h"

#include "glp.h"
#include "GraphicsDevice.h"

namespace Carpet {
    TerrainRenderer::TerrainRenderer(GraphicsDevice& gd, int detail, int layers)
        : render(gd.CreateNewRender<Vtx>(4 * 25, 2 * 25)) {
        // language=GLSL
        render->shader = Shader::New(
R"(
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
out vec2 vUV;
out vec4 vColor;
out float zLayer;

void main() {
    gl_Position = vec4(position.xy, position.z / 20.0f, 1.0);
    zLayer = position.z;
    vUV = position.xy * 0.5 + 0.5;
    vColor = color;
}
)",
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vUV;
in vec4 vColor;
in float zLayer;
uniform float uTime;
uniform vec2 focusPos;

uniform float fogFalloff;
uniform vec3 fogBlue, fogYellow;
uniform vec3 lightSource, cameraSource;
uniform float zOffset, xOffset, yOffset;
uniform float steepness, slopeZ;
uniform sampler2D terrainMap;

vec3 applyFog(vec3  col, // color of pixel
              float t,   // distance to point
              vec3  rd,  // camera to point
              vec3  lig) // sun direction
{
    float fogAmount = 1.0 - exp(-t * fogFalloff);
    float sunAmount = max(dot(rd, lig), 0.0);
    vec3  fogColor  = mix(fogBlue, fogYellow, pow(sunAmount, 8.0));
    return mix(col, fogColor, fogAmount);
}
void main() {
    float localX = vUV.x * 16 / 9;
    float z = 4 + zLayer + zOffset;
    vec3 point = vec3(localX, vUV.y, z * 0.1);
    vec2 focusOffset = focusPos * vec2(0.016, 0.009);
    vec3 actualLight = lightSource + vec3(focusOffset, 0) * 12;

    if (zLayer == 11.0) {
        float dist = length(point.xy - actualLight.xy), sun = 1 - smoothstep(0, 0.4, dist);
        vec3 result = mix(fogYellow, vColor.rgb, smoothstep(0, 0.6, dist));
        result *= (1 + 0.1 * sun);
        glColor = vec4(result, 1.0);
        return;
    }

    float height = yOffset + slopeZ * zLayer + focusOffset.y * zLayer - focusOffset.y * 3.7;
    float x = (xOffset + localX) * 0.3 * z + (uTime * 0.005) * zLayer - focusOffset.x * zLayer;
    float h = 2 * texture(terrainMap, vec2(x / 4.0, (zLayer + 0.5) / 10.0)).r - 1;
    if (vUV.y >= (height + (steepness / z) * h)) discard;

    vec3 dir = point - cameraSource;
    float dist = length(dir);
    vec3 result = applyFog(vColor.rgb, dist, dir / dist, normalize(actualLight - point));

    glColor = vec4(result, vColor.a);
}
)");

        GenerateTerrainMap(detail, layers);

        // cool colors: #001219, #1d3557, #457b9d, #a8dadc, #f1faee
        fColor anchorColors[] = { 0x001219_rgb, 0x1d3557_rgb, 0x457b9d_rgb, 0xa8dadc_rgb };
        int anchorPoints[]    = { 0,            3,            6,            9 };

        fColor colors[10];
        for (int i = 0, j = 1; i < 10; i++) {
            if (i > anchorPoints[j]) ++j;
            const int p = i - anchorPoints[j - 1], q = anchorPoints[j] - anchorPoints[j - 1];
            colors[i] = anchorColors[j - 1].Lerp(anchorColors[j], p, q);
        }

        SetupTerrain(colors, 10);
    }

    void TerrainRenderer::SetupTerrain(Span<const fColor> colors, int layers) {
        for (int z = 0; z < layers; ++z) {
            auto b = terrain.NewBatch();
            const float zf = (float)z;
            const fColor& color = colors[z];

            b.PushV({ { -1, -1, zf }, color });
            b.PushV({ { -1, +1, zf }, color });
            b.PushV({ { +1, +1, zf }, color });
            b.PushV({ { +1, -1, zf }, color });
            b.Quad(0, 1, 2, 3);
        }

        {
            auto b = terrain.NewBatch();
            const fColor color = 0xcce6ff_rgb;
            b.PushV({ { -1, -1, 11 }, color });
            b.PushV({ { -1, +1, 11 }, color });
            b.PushV({ { +1, +1, 11 }, color });
            b.PushV({ { +1, -1, 11 }, color });
            b.Quad(0, 1, 2, 3);
        }

        render.BeginContext();
        render.AddMesh(terrain);
        render.EndContext();
    }

    void TerrainRenderer::Render(GraphicsDevice& gd) {
        fv2 mouse = gd.GetIO().GetMousePos() / fv2(1920, 1080);
        mouse.y = 1 - mouse.y;
        focusPosition.LerpToward(mouse, 0.06);

        render.DrawContext({
            .arguments = {
                { "uTime", gd.GetIO().GetTime() },
                { "focusPos", focusPosition },
                { "fogFalloff",   fogFalloff },
                { "fogBlue",      fogBlue },
                { "fogYellow",    fogYellow },
                { "lightSource",  lightSource },
                { "cameraSource", cameraSource },
                { "zOffset",      zOffset },
                { "xOffset",      xOffset },
                { "yOffset",      yOffset },
                { "steepness",    steepness },
                { "slopeZ",       slopeZ },
            },
            .useDefaultArguments = false
        });
    }

    void TerrainRenderer::GenerateTerrainMap(int detail, int layers) {
        ArrayBox<byte> terrainMapImg = ArrayBox<byte>::AllocateUninit(layers << detail);

        static constexpr auto HASH2D = [] (const iv2& x) {
            int nx = x.x * 3 + x.y * 311,
                ny = x.x * 37 + x.y * 113;

            // 1D hash by Hugo Elias
            nx ^= nx << 13; ny ^= ny << 13;
            nx = nx * (nx * nx * 15731 + 789221) + 1376312589;
            ny = ny * (ny * ny * 15731 + 789221) + 1376312589;
            const fv2 v = { (nx & 0x0fffffff) / (float)0x0fffffff, (ny & 0x0fffffff) / (float)0x0fffffff };
            return -1 + 2 * v;
        };
        static constexpr auto NOISE = [] (const fv2& x) {
            const iv2 i = { (int)std::floor(x.x), (int)std::floor(x.y) };
            const fv2 f = x - (fv2)i;

            const fv2 u = f*f*f*(f*(f*6.0-15.0)+10.0);
            const fv2 du = 30.0*f*f*(f*(f-2.0)+1.0);

            const fv2 ga = HASH2D({ i.x + 0, i.y + 0 });
            const fv2 gb = HASH2D({ i.x + 1, i.y + 0 });
            const fv2 gc = HASH2D({ i.x + 0, i.y + 1 });
            const fv2 gd = HASH2D({ i.x + 1, i.y + 1 });

            const float va = ga.Dot(f);
            const float vb = gb.Dot(f) - gb.x;
            const float vc = gc.Dot(f) - gc.y;
            const float vd = gd.Dot(f) - gd.x - gd.y;

            fv2 dxdy = ga + u.x * (gb - ga) + u.y*(gc-ga)
                     + u.x*u.y*(ga-gb-gc+gd)
                     + du * (fv2(u.y, u.x)*(va-vb-vc+vd) + fv2(vb,vc) - va);

            return Tuple(va + u.x*(vb-va) + u.y*(vc-va) + u.x*u.y*(va-vb-vc+vd), dxdy);
        };

        for (usize k = 0; k < layers; ++k) {
            for (usize i = 0; i < 1 << detail; ++i) {
                fv2   p = { i / (float)(1 << (detail - 2)), (float)k + 4.0f };
                float a = 0.5;
                float b = 0.5;
                fv2   d = 0;
                for (int j = 0; j < 6; j++) {
                    auto [val, deriv] = NOISE(p);
                    d += deriv;
                    a += b * val / (1.0f + d.LenSq());
                    b *= 0.5;
                    p = p.ComplexMul(1.6, -1.2);
                }
                terrainMapImg[i | (k << detail)] = (byte)(a * 255.0f);
            }
        }
        terrainMap = Texture2D::New(terrainMapImg.Data(), { 1 << detail, layers },
            { .format = TextureFormat::RED, .internalformat = TextureIFormat::R_8,
              .border = TextureBorder::MIRRORED_REPEAT, .type = TID::BYTE }
        );
        terrainMap.Activate(TERRAIN_MAP_SLOT);
        render->shader.Bind();
        render->shader.SetUniformInt("terrainMap", TERRAIN_MAP_SLOT);
        GL::ActiveTexture(GL::TEXTURE0);
    }
}
