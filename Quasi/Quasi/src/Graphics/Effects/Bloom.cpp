#include "Bloom.h"

#include "glp.h"
#include "GraphicsDevice.h"
#include "RenderData.h"
#include "GLs/Render.h"

namespace Quasi::Graphics {
    Bloom::Bloom(const Math::iv2& screenDim) : screenDim(screenDim) {
        read = FrameBuffer::New();
        write = FrameBuffer::New();
        depthBuffer = RenderBuffer::New(TextureIFormat::DEPTH, screenDim);

        const TextureLoadParams params { .format = TextureFormat::RGBA, .internalformat = TextureIFormat::RGBA_32F, .type = TID::FLOAT };
        upsample = Texture2D::New(nullptr, screenDim, params);
        upsample.Bind();
        upsample.GenerateEmptyMipmaps(screenDim, params, LOD - 1);
        upsample.SetMaxMip(LOD - 1);
        upsample.SetMinifySample(TextureSample::LINEAR_NEAREST_MIP);

        downsample = Texture2D::New(nullptr, screenDim / 2, params);
        downsample.Bind();
        downsample.GenerateEmptyMipmaps(screenDim / 2, params, LOD - 1);
        downsample.SetMaxMip(LOD - 1);
        downsample.SetMinifySample(TextureSample::LINEAR_NEAREST_MIP);

        read.Bind();
        read.Attach(depthBuffer, AttachmentType::DEPTH);
        read.Attach(upsample);

        highPass = ShaderProgram::New(QShaderQuad$(430)
            "in vec2 vPosition;\n"
            "layout (location = 0) uniform float threshold;\n"
            "layout (location = 1) uniform float kneeOff;\n"
            "layout (location = 2) uniform sampler2D inputTex;\n"
            "layout (location = 0) out vec4 glColor;\n"
            "void main() {\n"
            "   vec4 input = textureLod(inputTex, vPosition, 0); \n"
            "   float brightness = dot(input.rgb, vec3(0.2126, 0.7152, 0.0722)); \n"
            "   float transparency = smoothstep(threshold - kneeOff, threshold, brightness);"
            "   glColor = vec4(input.rgb * transparency, 1.0);\n"
            "}"
        );
        downsampler = ShaderProgram::New(QShaderQuad$(430)
            "in vec2 vPosition;\n"
            "layout (location = 0) uniform float lod;\n"
            "layout (location = 1) uniform sampler2D imgInput;\n"
            "layout (location = 0) out vec4 glColor;\n"
            "void main() {\n"
            "   vec2 s = 1.0 / vec2(textureSize(imgInput, int(lod))); \n"
            "   vec3 A = textureLod(imgInput, vPosition + s * vec2(-1.0, -1.0), lod).rgb;"
            "   vec3 B = textureLod(imgInput, vPosition + s * vec2( 0.0, -1.0), lod).rgb;"
            "   vec3 C = textureLod(imgInput, vPosition + s * vec2( 1.0, -1.0), lod).rgb;"
            "   vec3 D = textureLod(imgInput, vPosition + s * vec2(-0.5, -0.5), lod).rgb;"
            "   vec3 E = textureLod(imgInput, vPosition + s * vec2( 0.5, -0.5), lod).rgb;"
            "   vec3 F = textureLod(imgInput, vPosition + s * vec2(-1.0,  0.0), lod).rgb;"
            "   vec3 G = textureLod(imgInput, vPosition                       , lod).rgb;"
            "   vec3 H = textureLod(imgInput, vPosition + s * vec2( 1.0,  0.0), lod).rgb;"
            "   vec3 I = textureLod(imgInput, vPosition + s * vec2(-0.5,  0.5), lod).rgb;"
            "   vec3 J = textureLod(imgInput, vPosition + s * vec2( 0.5,  0.5), lod).rgb;"
            "   vec3 K = textureLod(imgInput, vPosition + s * vec2(-1.0,  1.0), lod).rgb;"
            "   vec3 L = textureLod(imgInput, vPosition + s * vec2( 0.0,  1.0), lod).rgb;"
            "   vec3 M = textureLod(imgInput, vPosition + s * vec2( 1.0,  1.0), lod).rgb;"
            "   vec3 result = (D + E + G + I + J) * 0.125 + (B + F + H + L) * 0.0625 + (A + C + K + M) * 0.03125;"
            "   glColor = vec4(result, 1.0); \n"
            "}"
        );

        merge = ShaderProgram::New(QShaderQuad$(430)
            "in vec2 vPosition;\n"
            "layout (location = 0) uniform sampler2D imgInput;\n"
            "layout (location = 0) out vec4 glColor;\n"
            "void main() {\n"
            "   vec2 s = 1.0 / vec2(textureSize(imgInput, 6)); \n"
            "   vec3 upsampled = (textureLod(imgInput, vPosition,                6).rgb +"
            "                     textureLod(imgInput, vPosition + vec2(s.x, 0), 6).rgb +"
            "                     textureLod(imgInput, vPosition + vec2(0, s.y), 6).rgb +"
            "                     textureLod(imgInput, vPosition + s,            6).rgb) * 0.25;"
            "   vec3 result = upsampled + textureLod(imgInput, vPosition, 5).rgb;"
            "   glColor = vec4(result, 1.0); \n"
            "}"
        );

        upsampler = ShaderProgram::New(QShaderQuad$(430)
            "in vec2 vPosition;\n"
            "layout (location = 0) uniform float lod;\n"
            "layout (location = 1) uniform sampler2D imgInput;\n"
            "layout (location = 2) uniform sampler2D imgOutput;\n"
            "layout (location = 0) out vec4 glColor;\n"
            "void main() {\n"
            "   vec2 s = 1.0 / vec2(textureSize(imgOutput, int(lod))); \n"
            "   vec3 upsampled = (textureLod(imgOutput, vPosition + s,               lod).rgb +"
            "                     textureLod(imgOutput, vPosition + vec2(s.x, -s.y), lod).rgb +"
            "                     textureLod(imgOutput, vPosition + vec2(-s.x, s.y), lod).rgb +"
            "                     textureLod(imgOutput, vPosition - s,               lod).rgb) * 0.25;"
            "   vec3 result = upsampled + textureLod(imgInput, vPosition, lod - 1).rgb;"
            "   glColor = vec4(result, 1.0); \n"
            "}"
        );

        addBack = ShaderProgram::New(QShaderQuad$(430)
            "in vec2 vPosition;\n"
            "layout (location = 0) uniform float intensity;\n"
            "layout (location = 1) uniform sampler2D imgInput;\n"
            "layout (location = 0) out vec4 glColor;\n"
            "void main() {\n"
            "   vec3 result = textureLod(imgInput, vPosition, 0).rgb + intensity * textureLod(imgInput, vPosition, 1).rgb; \n"
            "   float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722)); \n"
            "   result *= (4 / (4 + brightness));"
            "   glColor = vec4(result, 1.0); \n"
            "}"
        );
    }

    void Bloom::RenderToLevel(int level) {
        GL::Viewport(0, 0, screenDim.x >> level, screenDim.y >> level);
        GL::DrawArrays(GL::TRIANGLES, 0, 3);
    }

    void Bloom::DrawDown(int level) {
        // we save the level 0 mip because we dont actually use it
        write.Attach(downsample, level - 1);
    }

    void Bloom::DrawUp(int level) {
        read.Attach(upsample, level);
    }

    void Bloom::SetToRenderTarget() {
        read.BindDrawDest();
        GL::Viewport(0, 0, screenDim.x, screenDim.y);
    }

    void Bloom::ApplyEffect() {
        constexpr u32 UNIF_THRESHOLD = 0, UNIF_INTENSITY = 0,
                      UNIF_KNEEOFF = 1,
                      UNIF_HP_INPUT_TEXTURE = 2,
                      UNIF_TEXTURE_LOD = 0,
                      UNIF_INPUT_TEXTURE = 1, UNIF_OUTPUT_TEXTURE = 2,
                      SLOT_DWN = 1, SLOT_UP = 0;

        // HOW THIS WORKS:
        /*
         * LOD |            [ SCREEN  ]
         *     |                 v (drawn to framebuffer)
         *  0  |            [UPSAMP #0] --------v
         *     | (add back)    ^   ^            |       (high pass filter)
         *  1  |            [UPSAMP #0]   [DOWNSAMP #0]
         *     |                 ^              v
         *  2  |            [UPSAMP #1]   [DOWNSAMP #1]
         *     | (upsample)      ^              v
         *  3  |            [UPSAMP #2]   [DOWNSAMP #2]
         *     |                 ^              v       (downsample)
         *  4  |            [UPSAMP #3]   [DOWNSAMP #3]
         *     |                 ^              v
         *  5  |            [UPSAMP #4] < [DOWNSAMP #4]
         *     |                 |              v
         *  6  |    (merge)      ^------- [DOWNSAMP #5]
         */

        Render::DisableDepth();
        Render::DisableBlend();

        upsample.Activate(SLOT_UP);
        downsample.Activate(SLOT_DWN);
        GL::BindVertexArray(GraphicsDevice::GetEmptyVAO().rendererID);

        write.Bind();
        DrawDown(1);

#pragma region High Pass Filter
        // CURRENT STATE: read `upsample[0]` draw to `write`/`downsample[1]`
        highPass.Bind();
        GL::Uniform1f(UNIF_THRESHOLD, threshold);
        GL::Uniform1f(UNIF_KNEEOFF, kneeOff);
        GL::Uniform1i(UNIF_HP_INPUT_TEXTURE, SLOT_UP);
        RenderToLevel(1);
#pragma endregion

#pragma region Downsampling
        // CURRENT STATE: read from `downsample[1+]` draw to `write`/`downsample[2+]`
        downsampler.Bind();
        GL::Uniform1i(UNIF_INPUT_TEXTURE, SLOT_DWN);
        for (int i = 2; i <= LOD; ++i) {
            DrawDown(i);
            GL::Uniform1f(UNIF_TEXTURE_LOD, (float)(i - 2));
            RenderToLevel(i);
        }
#pragma endregion

        read.Bind();
        DrawUp(LOD - 1);

#pragma region Merge Filter
        // CURRENT STATE: read from `downsample[5 & 6]` draw to `write`/`upsample[5]`
        merge.Bind();
        GL::Uniform1i(UNIF_INPUT_TEXTURE, SLOT_DWN);
        RenderToLevel(LOD - 1);
#pragma endregion

#pragma region Upsampling
        // CURRENT STATE: read from `upsample[5-] & downsample[4-]` draw to `write`/`upsample[4-]`
        upsampler.Bind();
        GL::Uniform1i(UNIF_INPUT_TEXTURE, SLOT_DWN);
        GL::Uniform1i(UNIF_OUTPUT_TEXTURE, SLOT_UP);
        for (int i = LOD - 1; i --> 1;) {
            DrawUp(i);
            GL::Uniform1f(UNIF_TEXTURE_LOD, (float)(i + 1));
            RenderToLevel(i);
        }
#pragma endregion

#pragma region Final Overlay
        // CURRENT STATE: read from `upsample[1] & upsample[0]` draw to `screen`
        addBack.Bind();
        GL::Uniform1f(UNIF_INTENSITY, intensity);
        GL::Uniform1i(UNIF_INPUT_TEXTURE, SLOT_UP);
        DrawUp(0);
        read.Unbind();
        const Math::iv2 actualScreenDim = GraphicsDevice::GetDeviceInstance().GetWindowSize();
        GL::Viewport(0, 0, actualScreenDim.x, actualScreenDim.y);
        GL::DrawArrays(GL::TRIANGLES, 0, 3);
#pragma endregion

        Render::EnableDepth();
        Render::EnableBlend();
    }
}
