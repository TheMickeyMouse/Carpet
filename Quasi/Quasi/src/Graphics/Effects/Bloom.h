#pragma once
#include "GLs/FrameBuffer.h"
#include "GLs/RenderBuffer.h"
#include "GLs/Shader.h"
#include "GLs/Texture.h"

namespace Quasi::Graphics {
    class RenderData;

    struct Bloom {
        FrameBuffer read, write;
        RenderBuffer depthBuffer;
        Texture2D upsample, downsample;
        ShaderProgram highPass, downsampler, merge, upsampler, addBack;
        Math::iv2 screenDim;

        float threshold = 1.0f, kneeOff = 0.3f, intensity = 0.2f;

        static constexpr u32 LOD = 6;

        Bloom(const Math::iv2& screenDim);
    private:
        void RenderToLevel(int level);
        void DrawDown(int level);
        void DrawUp(int level);
    public:
        void SetToRenderTarget();
        void ApplyEffect();
    };
} // Quasi
