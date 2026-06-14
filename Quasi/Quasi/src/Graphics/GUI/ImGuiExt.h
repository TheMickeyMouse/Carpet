#pragma once
#include <imgui.h>
#include "Utils/Str.h"
#include "Utils/Type.h"
#include "Utils/Math/Rect.h"
#include "Utils/Math/Color.h"

namespace Quasi::Math {
    struct Rotor3D;
    struct Transform3D;
}

namespace Quasi::Graphics {
    class CameraController3D;
    class Light;
}

namespace ImGui {
#define Q Quasi::
#define Q_IMGUI_EDITOR(NAME, ...) void NAME(Q Str title, __VA_ARGS__, float width = Q f32s::NAN)

    template <class T> ImGuiDataType ImGuiDataEnum();

    float GetUsableWidth();
    float GetRemWidth(float width = Q f32s::NAN);
    float GetLastItemWidth();
    float GetSpacingWidth();
    float GetItemDefaultWidth(float totalWidth = Q f32s::NAN);
    float GetItemRemainingWidth(float totalWidth = Q f32s::NAN);

    void DisplaySimpleIcon(const char* text, const Q Math::fColor3& bgColor);

    void DisplayTextCropped(Q Str text, float width);

    void EditString(Q Str label, Q String& string);

    template <Q Numeric T>
    Q_IMGUI_EDITOR(EditScalar, T& value, float speed = 1, Q NoInfer<Q Option<Q Range<T>>> range = nullptr);

    template <Q Numeric T>
    Q_IMGUI_EDITOR(EditScalarWithIcon, const Q Math::fColor3& color,
        T& value, float speed = 1, Q NoInfer<Q Option<Q Range<T>>> range = nullptr, Q Str fmt = {}) {
        PushID(title.Data());
        DisplaySimpleIcon(title.Data(), color);

        SetNextItemWidth(GetRemWidth(width) - GetLastItemWidth() - GetSpacingWidth());
        SameLine();
        DragScalar("##value", ImGuiDataEnum<T>(), &value, speed, range ? &range->min : nullptr, range ? &range->max : nullptr, fmt.Data());
        PopID();
    }

    template <class T, Q usize N>
    Q_IMGUI_EDITOR(EditVector, Q Math::Vector<T, N>& vector, float speed = 1, Q NoInfer<const Q Option<Q Math::Rect<T, N>>&> range = nullptr);

    template <class T>
    Q_IMGUI_EDITOR(EditRange, Q Range<T>& range, float speed = 1, Q NoInfer<const Q Option<Q Range<T>>&> constraint = nullptr);

    template <class T, Q usize N>
    Q_IMGUI_EDITOR(EditRect, Q Math::Rect<T, N>& range, float speed = 1, Q NoInfer<const Q Option<Q Math::Rect<T, N>>&> constraint = nullptr);

    Q_IMGUI_EDITOR(EditRotation2D, Q Math::Rotor2D& rot2);
    Q_IMGUI_EDITOR(EditRotation3D, Q Math::Rotor3D& rot3);

    Q_IMGUI_EDITOR(EditYawPitch, float& yaw, float& pitch);

    template <class T, bool A>
    Q_IMGUI_EDITOR(EditColor, Q Math::IColor<T, A>& color);

    Q_IMGUI_EDITOR(EditTransform, Q Math::Transform2D& transform, float speed = 1);
    Q_IMGUI_EDITOR(EditTransform, Q Math::Transform3D& transform, float speed = 1);

    Q_IMGUI_EDITOR(EditCameraController, Q Graphics::CameraController3D& camera);
    Q_IMGUI_EDITOR(EditLight, Q Graphics::Light& light);

#undef Q
#undef Q_IMGUI_EDITOR
} // ImGui