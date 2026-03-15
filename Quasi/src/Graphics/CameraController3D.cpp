#include "CameraController3D.h"

#include "GraphicsDevice.h"

namespace Quasi::Graphics {
    Math::fv3 CameraController3D::Right() const { return worldFront.Cross(worldUp); }

    void CameraController3D::Update(GraphicsDevice& gd, const float dt) {
        using namespace Math;
        using namespace IO;
        const auto& io = gd.GetIO();
        if (io.GetKey(Key::ESCAPE).OnPress()) Toggle(gd);

        if (UsesSmoothZoom()) {
            viewFov = std::lerp(fov, viewFov, std::exp2f(-smoothZoom * dt));
        } else {
            viewFov = fov;
        }

        if (!enabled) { return; }
        const fv3 localRight = -(Right() * std::cos(yaw) + worldFront * std::sin(yaw));
        const fv3 localFront = worldUp.Cross(localRight);
        if (io['W'].Pressed())      position += localFront * speed * dt;
        if (io['S'].Pressed())      position -= localFront * speed * dt;
        if (io['D'].Pressed())      position += localRight * speed * dt;
        if (io['A'].Pressed())      position -= localRight * speed * dt;
        if (io["Space"].Pressed())  position += fv3::Up()   * speed * dt;
        if (io["Shift"].Pressed()) position += fv3::Down() * speed * dt;

        if (io[Key::CAPS_LOCK].OnPress()) fov = fovRange.max * zoomRatio;
        if (io[Key::CAPS_LOCK].OnRelease()) fov = fovRange.max;

        if (io[Key::LCONTROL].OnPress()) speed *= 2;
        if (io[Key::LCONTROL].OnRelease()) speed /= 2;

        if (io[Key::CAPS_LOCK].Pressed()) {
            fov -= (float)io.GetMouseScrollDelta();
            fov = fovRange.Clamp(fov);
        }

        const fv2 delta = io.GetMousePosDelta();

        yaw   += delta.x * -(sensitivity * dt);
        pitch += delta.y *  (sensitivity * dt);
        pitch = std::clamp(pitch, HALF_PI * -0.95f, HALF_PI * 0.95f);
    }

    void CameraController3D::Toggle(GraphicsDevice& gd) {
        enabled ^= true;
        if (enabled) {
            gd.GetIO().CursorLock();
        } else {
            gd.GetIO().CursorShow();
        }
    }

    Math::Matrix3D CameraController3D::GetViewMat() const {
        return GetViewTransform().IntoMatrix().InvTransRot();
    }

    Math::Transform3D CameraController3D::GetViewTransform() const {
        // const Math::fv3 front =
        //     Right()    * (std::cos(yaw) * std::cos(pitch)) + // like x
        //     worldFront * (std::sin(yaw) * std::cos(pitch)) +
        //     worldUp    * std::sin(pitch);
        // return { -position, 1, Math::Rotor3D::LookAt(front, worldFront).Inverse() };
        return { position, 1, Math::Rotor3D::RotateAxis(worldUp, Math::Radians(yaw)) + Math::Rotor3D::RotateAxis(Right(), Math::Radians(pitch)) };
    }

    Math::Matrix3D CameraController3D::GetProjMat() const {
        const float aspect = GraphicsDevice::GetDeviceInstance().GetWindowSize().AspectRatio();
        return Math::Matrix3D::PerspectiveFov(Math::Degrees(viewFov), aspect, 0.01f, 100.0f);
    }
}
