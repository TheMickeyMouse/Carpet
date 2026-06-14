#pragma once
#include <cmath>

#include "Utils/Math/Transform3D.h"

namespace Quasi::Graphics {
    class GraphicsDevice;

    class CameraController3D {
    public:
        Math::fv3 worldUp = Math::fv3::Up(), worldFront = Math::fv3::Front();

        Math::fv3 position = { 0, 0, -2 };
        float yaw = 0.0f, pitch = 0.0f; // yaw is looking A <-> B rotation, pitch is ^^^ rotation

        float speed = 1.5f, sensitivity = 0.12f, fov = 45.0f, viewFov = 45.0f;
        fRange fovRange = { 1.0f, 45.0f };
        float zoomRatio = 0.5f;

        bool enabled = false;
        float smoothZoom = -1.0f;

        Math::fv3 Right() const;

        void Update(GraphicsDevice& gd, float dt);
        void Toggle(GraphicsDevice& gd);

        Math::Matrix3D GetViewMat() const;
        Math::Transform3D GetViewTransform() const;
        Math::Matrix3D GetProjMat() const;

        bool UsesSmoothZoom() const { return !std::signbit(smoothZoom); }
    };
}
