#include "TerrainRenderer.h"

#include "GraphicsDevice.h"

namespace Carpet {
    TerrainRenderer::TerrainRenderer(GraphicsDevice& gd)
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
    gl_Position = vec4(position.xy, 0.0, 1.0);
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
uniform vec2 mousePos;

vec2 hash( in ivec2 p )  // this hash is not production ready, please
{                        // replace this by something better
    // 2D -> 1D
    ivec2 n = p.x*ivec2(3,37) + p.y*ivec2(311,113);

    // 1D hash by Hugo Elias
	n = (n << 13) ^ n;
    n = n * (n * n * 15731 + 789221) + 1376312589;
    return -1.0+2.0*vec2( n & ivec2(0x0fffffff))/float(0x0fffffff);
}
vec3 noised( in vec2 x )
{
    ivec2 i = ivec2(floor( x ));
    vec2 f = fract( x );

    vec2 u = f*f*f*(f*(f*6.0-15.0)+10.0);
    vec2 du = 30.0*f*f*(f*(f-2.0)+1.0);

    vec2 ga = hash( i + ivec2(0.0,0.0) );
    vec2 gb = hash( i + ivec2(1.0,0.0) );
    vec2 gc = hash( i + ivec2(0.0,1.0) );
    vec2 gd = hash( i + ivec2(1.0,1.0) );

    float va = dot( ga, f - vec2(0.0,0.0) );
    float vb = dot( gb, f - vec2(1.0,0.0) );
    float vc = dot( gc, f - vec2(0.0,1.0) );
    float vd = dot( gd, f - vec2(1.0,1.0) );

    return vec3( va + u.x*(vb-va) + u.y*(vc-va) + u.x*u.y*(va-vb-vc+vd),   // value
                 ga + u.x*(gb-ga) + u.y*(gc-ga) + u.x*u.y*(ga-gb-gc+gd) +  // derivatives
                 du * (u.yx*(va-vb-vc+vd) + vec2(vb,vc) - va));
}

const mat2 m = mat2(0.8, -0.6, 0.6, 0.8);
// from inigo quilez
float fbm(in vec2 p) {
    float a = 0.0;
    float b = 1.0;
    vec2  d = vec2(0.0,0.0);
    for (int i = 0; i < 8; i++) {
        vec3 n=noised(p);
        d += n.yz;
        a += b*n.x/(1.0+dot(d,d));
        b *= 0.5;
        p = m*p*2.0;
    }
    return a;
}
vec3 applyFog( in vec3  col,   // color of pixel
               in float t,     // distance to point
               in vec3  rd,    // camera to point
               in vec3  lig )  // sun direction
{
    float fogAmount = 1.0 - exp(-t * 0.15);
    float sunAmount = max( dot(rd, lig), 0.0 );
    vec3  fogColor  = mix( vec3(0.5,0.6,0.7), // blue
                           vec3(1.0,0.9,0.7), // yellow
                           pow(sunAmount,5.0) );
    return mix(col, fogColor, fogAmount) * 1.05;
}
const vec3 kLightSource = vec3(1.25, 0.6, 2.4);
void main() {
    float localX = vUV.x * 16 / 9;
    float z = 4 + zLayer;
    float height = zLayer == 11.0 ? 2.0 : 0.16 + 0.039 * zLayer + mousePos.y * 0.3 / z;
    float x = localX * 0.3 * z + (uTime * 0.005) * zLayer - mousePos.x * 0.2 / z;
    vec4 result = vUV.y < (height + (3.5 / z) * fbm(vec2(x, z))) ? vColor : vec4(0.0);

    vec3 point = vec3(localX, vUV.y, z * 0.1);
    vec3 dir = point - vec3(0.5, 0.5, -1.5);
    float dist = length(dir);
    result.rgb = applyFog(result.rgb, dist, dir / dist, normalize(kLightSource - point));

    glColor = result;
}
)");

        // cool colors: #001219, #1d3557, #457b9d, #a8dadc, #f1faee
        fColor anchorColors[] = { 0x001219_rgb, 0x1d3557_rgb, 0x457b9d_rgb, 0xa8dadc_rgb };
        int anchorPoints[]    = { 0,            3,            6,            9 };

        fColor colors[10];
        for (int i = 0, j = 1; i < 10; i++) {
            if (i > anchorPoints[j]) ++j;
            int p = i - anchorPoints[j - 1], q = anchorPoints[j] - anchorPoints[j - 1];
            colors[i] = anchorColors[j - 1].Lerp(anchorColors[j], p, q);
        }

        SetupTerrain(colors, 10);
    }

    void TerrainRenderer::SetupTerrain(Span<const fColor> colors, int layers) {
        {
            auto b = terrain.NewBatch();
            const fColor color = 0xf1faee_rgb;
            b.PushV({ { -1, -1, 11 }, color });
            b.PushV({ { -1, +1, 11 }, color });
            b.PushV({ { +1, +1, 11 }, color });
            b.PushV({ { +1, -1, 11 }, color });
            b.Quad(0, 1, 2, 3);
        }

        for (int z = layers; z --> 0; ) {
            auto b = terrain.NewBatch();
            const float zf = (float)z;
            const fColor& color = colors[z];

            b.PushV({ { -1, -1, zf }, color });
            b.PushV({ { -1, +1, zf }, color });
            b.PushV({ { +1, +1, zf }, color });
            b.PushV({ { +1, -1, zf }, color });
            b.Quad(0, 1, 2, 3);
        }
        render.BeginContext();
        render.AddMesh(terrain);
        render.EndContext();
    }

    void TerrainRenderer::Render(GraphicsDevice& gd) {
        const fv2 mouse = gd.GetIO().GetMousePos() / fv2(1920, 1080);
        render.DrawContext({
            .arguments = {
                { "uTime", gd.GetIO().GetTime() },
                { "mousePos", fv2(mouse.x, 1 - mouse.y) },
            },
            .useDefaultArguments = false
        });
    }
}
