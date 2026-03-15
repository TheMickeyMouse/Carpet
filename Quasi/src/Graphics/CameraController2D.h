#pragma once
#include "Utils/Math/Transform3D.h"
#include "Utils/Math/Vector.h"

namespace Quasi::Graphics {
    class GraphicsDevice;

    class CameraController2D {
    public:
        Math::fv2 position;
        float scale = 1.0f, displayScale = 1.0f, speed = 1.2f;
        bool useSmoothZoom = true, enabled = true;

        void Update(GraphicsDevice& gd, float dt);
        void Toggle();

        Math::fRect2D     GetViewport() const;
        Math::Transform2D GetViewTransform() const;
        Math::Transform3D GetViewTransform3D() const;
        Math::Matrix2D    GetViewMatrix() const;
        Math::Matrix3D    GetViewMatrix3D() const;
    };
}
