#include "CameraController2D.h"

#include "GraphicsDevice.h"

namespace Quasi::Graphics {
    void CameraController2D::Update(GraphicsDevice& gd, float dt) {
        using namespace Math;
        using namespace IO;

        const auto& io = gd.GetIO();

        if (useSmoothZoom) {
            displayScale = std::lerp(scale, displayScale, std::exp2f(-80.0f * dt));
        } else {
            displayScale = scale;
        }

        if (!enabled) { return; }
        if (io['W'].Pressed()) position.y += scale * speed * dt;
        if (io['S'].Pressed()) position.y -= scale * speed * dt;
        if (io['D'].Pressed()) position.x += scale * speed * dt;
        if (io['A'].Pressed()) position.x -= scale * speed * dt;

        if (io[Key::CAPS_LOCK].Pressed())   scale = 3;
        if (io[Key::CAPS_LOCK].Pressed()) scale = 1;

        if (io[Key::LCONTROL].Pressed()) speed *= 2;
        if (io[Key::LCONTROL].Pressed()) speed /= 2;

        scale += (float)io.GetMouseScrollDelta() * scale * 0.06f;
        if (io.MiddleMouse().Pressed()) {
            fv2 delta = io.GetMousePosDelta().FlipY();
            position -= delta / scale;
        }
    }

    void CameraController2D::Toggle() {
        enabled ^= true;
    }

    Math::fRect2D CameraController2D::GetViewport() const {
        const Math::fv2 winsize = (Math::fv2)GraphicsDevice::GetDeviceInstance().GetWindowSize();
        return Math::fRect2D::FromCenter(position, winsize / displayScale);
    }

    Math::Transform2D CameraController2D::GetViewTransform() const {
        return { position, 1.0f / displayScale, {} };
    }

    Math::Transform3D CameraController2D::GetViewTransform3D() const {
        const float invScale = 1.0f / displayScale;
        return { position.AddZ(0), { invScale, invScale, 1 }, {} };
    }

    Math::Matrix2D CameraController2D::GetViewMatrix() const {
        return Math::Matrix2D::Transform(-position, displayScale, {});
    }

    Math::Matrix3D CameraController2D::GetViewMatrix3D() const {
        return Math::Matrix3D::Transform(-position.AddZ(0), { displayScale, displayScale, 1 }, {});
    }
}
