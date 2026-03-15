#pragma once
#include "Utils/Math/Vector.h"
#include "Utils/Math/Color.h"
#include "Utils/Variant.h"

namespace Quasi::Graphics {
    struct SunLight {
        Math::fv3 direction;
    };

    struct PointLight {
        Math::fv3 position;
        float constant, linear, quadratic;
    };

    struct FlashLight {
        Math::fv3 position;
        Math::Radians yaw, pitch, innerCut, outerCut;
    };

    class Light : public Variant<SunLight, PointLight, FlashLight> {
    public:
        Math::fColor color;
    public:
        Math::fv3 Position() const;
        Math::fv3 Direction() const;
    };
}
