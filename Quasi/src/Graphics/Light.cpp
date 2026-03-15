#include "Light.h"

namespace Quasi::Graphics {
    Math::fv3 Light::Position() const {
        return Visit<Math::fv3>([]<class L> (const L& light) {
            if constexpr (ConvTo<L, SunLight>) return -light.direction;
            else return light.position;
        });
    }

    Math::fv3 Light::Direction() const {
        return Visit<Math::fv3>(
            [](const SunLight&   sun)   { return sun.direction; },
            [](const PointLight& point) { return -point.position; },
            [](const FlashLight& flash) { return Math::fv3::FromSpheric(1, flash.yaw, flash.pitch); }
        );
    }
}
