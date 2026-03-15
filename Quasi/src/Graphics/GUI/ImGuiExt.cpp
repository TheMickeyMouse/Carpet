#include "ImGuiExt.h"

#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include "Utils/Array.h"

#include "Complex.h"
#include "CameraController3D.h"
#include "Light.h"

#include "Utils/Math/Transform2D.h"
#include "Utils/Math/Transform3D.h"
#include "Utils/Text/Formatting.h"

namespace ImGui {
    static const Quasi::Math::fColor3 COLOR_X_AXIS  = Quasi::Math::fColor3::Better::Red();
    static const Quasi::Math::fColor3 COLOR_Y_AXIS  = Quasi::Math::fColor3::Better::Green();
    static const Quasi::Math::fColor3 COLOR_Z_AXIS  = Quasi::Math::fColor3::Better::Blue();
    static const Quasi::Math::fColor3 COLOR_W_AXIS  = Quasi::Math::fColor3::Better::Yellow();
    static const Quasi::Math::fColor3 COLOR_ALPHA   = Quasi::Math::fColor3::Better::Gray();
    static const Quasi::Math::fColor3 COLOR_X_ANGLE = Quasi::Math::fColor3::Better::Orange();
    static const Quasi::Math::fColor3 COLOR_Y_ANGLE = Quasi::Math::fColor3::Better::Cyan();
    static const Quasi::Math::fColor3 COLOR_Z_ANGLE = Quasi::Math::fColor3::Better::Purple();

    float GetUsableWidth() {
        return GetWindowWidth() - 2 * GetStyle().WindowPadding.x;
    }

    float GetRemWidth(float width) {
        return std::isnan(width) ? GetUsableWidth() : width;
    }

    float GetLastItemWidth() {
        return GetItemRectSize().x;
    }

    float GetSpacingWidth() {
        return GetStyle().ItemSpacing.x;
    }

    float GetItemDefaultWidth(float totalWidth) {
        totalWidth = GetRemWidth(totalWidth);
        return totalWidth * 0.80f;
    }

    float GetItemRemainingWidth(float totalWidth) {
        totalWidth = GetRemWidth(totalWidth);
        return totalWidth * 0.20f - GetCurrentWindow()->DC.Indent.x;
    }

#define Q Quasi::
#define Q_IMGUI_EDITOR(NAME, ...) void NAME(Q Str title, __VA_ARGS__, float width)

    void DisplaySimpleIcon(const char* text, const Q Math::fColor3& bgColor) {
        const ImVec4 c = { bgColor.r, bgColor.g, bgColor.b, 1 };
        PushStyleColor(ImGuiCol_Button,        c);
        PushStyleColor(ImGuiCol_ButtonActive,  c);
        PushStyleColor(ImGuiCol_ButtonHovered, c);
        PushID("icon");
        Button(text);
        PopID();
        PopStyleColor(3);
    }

    void DisplayTextCropped(Q Str text, float width) {
        const char* begin = text.Data(), *end = begin + text.Length();
        const ImVec2 textSize = CalcTextSize(begin, end),
                     cursor = GetCursorScreenPos();
        const float clipX = cursor.x + width;
        const ImRect bb { cursor, { cursor.x + std::min(textSize.x, width), cursor.y + textSize.y } };

        ItemSize({ std::min(textSize.x, width), textSize.y } , 0.0f);
        if (!ItemAdd(bb, 0))
            return;

        RenderTextEllipsis(GetWindowDrawList(), cursor, { clipX, cursor.y + textSize.y }, clipX, clipX, begin, end, &textSize);
    }

    void EditString(Q Str label, Q String& string) {
        string.AddNullTerm();
        auto* const callback = +[] (ImGuiInputTextCallbackData* data) -> int {
            Q String* s = (Q String*)data->UserData;
            if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
                s->Resize(data->BufTextLen + 1);
                data->Buf = (char*)s->Data();
            }
            return 0;
        };
        InputTextMultiline(label.Data(), string.Data(), string.Capacity(), ImVec2(0, 0), ImGuiInputTextFlags_CallbackResize, callback, &string);
        string.TruncNullTerm();
    }

    template <class T> ImGuiDataType ImGuiDataEnum() {
        if constexpr (Q SameAs<T, Q f32>) return ImGuiDataType_Float;
        if constexpr (Q SameAs<T, Q f64>) return ImGuiDataType_Double;
        if constexpr (Q SameAs<T, Q u8 >) return ImGuiDataType_U8;
        if constexpr (Q SameAs<T, Q i8 >) return ImGuiDataType_S8;
        if constexpr (Q SameAs<T, Q u16>) return ImGuiDataType_U16;
        if constexpr (Q SameAs<T, Q i16>) return ImGuiDataType_S16;
        if constexpr (Q SameAs<T, Q u32>) return ImGuiDataType_U32;
        if constexpr (Q SameAs<T, Q i32>) return ImGuiDataType_S32;
        if constexpr (Q SameAs<T, Q u64>) return ImGuiDataType_U64;
        if constexpr (Q SameAs<T, Q i64>) return ImGuiDataType_S64;
        return ImGuiDataType_COUNT;
    }

    template <Q Numeric T>
    Q_IMGUI_EDITOR(EditScalar, T& value, float speed, Q NoInfer<Q Option<Q Range<T>>> range) {
        width = GetRemWidth(width);

        DisplayTextCropped(title, GetItemRemainingWidth(width) - GetSpacingWidth());

        SetNextItemWidth(GetItemDefaultWidth(width));
        SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());

        PushID(title.Data());
        DragScalar("", ImGuiDataEnum<T>(), &value, speed,
            range ? &range->min : nullptr, range ? &range->max : nullptr);
        PopID();
    }

    template <class T, Q usize N>
    Q_IMGUI_EDITOR(EditVector, Q Math::Vector<T, N>& vector, float speed, Q NoInfer<const Q Option<Q Math::Rect<T, N>>&> range) {
        width = GetRemWidth(width);

        DisplayTextCropped(title, GetItemRemainingWidth(width) - GetSpacingWidth());
        SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());

        const float fullWidth = GetItemDefaultWidth(width) - (float)(N - 1) * GetSpacingWidth(),
                    unitWidth = fullWidth / (float)N;

        for (Q u32 i = 0; i < N; ++i) {
            PushID(title.Data());
            EditScalarWithIcon(
                &"X:\0Y:\0Z:\0W:"[i * 3],
                Q Array { COLOR_X_AXIS, COLOR_Y_AXIS, COLOR_Z_AXIS, COLOR_W_AXIS }[i], // amazing hack
                vector[i],
                speed,
                range ? Q Options::Some(range->RangeN(i)) : nullptr,
                {},
                unitWidth
            );
            if (i != N - 1) SameLine();
            PopID();
        }
    }

    template <class T>
    Q_IMGUI_EDITOR(EditRange, Q Range<T>& range, float speed, Q NoInfer<const Q Option<Q Range<T>>&> constraint) {
        width = GetRemWidth(width);

        DisplayTextCropped(title, GetItemRemainingWidth(width) - GetSpacingWidth());

        SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());
        const float fullWidth = GetItemDefaultWidth(width) - GetSpacingWidth();
        PushID(title.Data());
        EditScalarWithIcon("Min", COLOR_ALPHA, range.min, speed, constraint, {}, fullWidth * 0.5f);
        SameLine();
        EditScalarWithIcon("Max", COLOR_ALPHA, range.max, speed, constraint, {}, fullWidth * 0.5f);
        PopID();
    }

    template <class T, Q usize N>
    Q_IMGUI_EDITOR(EditRect, Q Math::Rect<T, N>& range, float speed, Q NoInfer<const Q Option<Q Math::Rect<T, N>>&> constraint) {
        width = GetRemWidth(width);

        DisplayTextCropped(title, GetItemRemainingWidth(width) - GetSpacingWidth());

        SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());
        const float rWidth = GetItemDefaultWidth(width);
        PushID(title.Data());
        EditVector("Min", range.min, speed, constraint, rWidth);
        Indent(GetItemRemainingWidth(width));
        EditVector("Max", range.max, speed, constraint, rWidth);
        PopID();
        Unindent(GetItemRemainingWidth(width));
    }

    Q_IMGUI_EDITOR(EditRotation2D, Q Math::Rotor2D& rot2) {
        width = GetRemWidth(width);

        float theta = rot2.Angle().Degrees();
        DisplayTextCropped(title, GetItemRemainingWidth(width) - GetSpacingWidth());

        SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());

        const float w = GetItemDefaultWidth(width);
        PushID(title.Data());
        EditScalarWithIcon((const char*)u8"θ:", COLOR_Z_ANGLE, theta, 1, Q fRange { -180, 180 }, "%f°", w);
        PopID();

        rot2 = { Q Math::Degrees(theta) };
    }

    Q_IMGUI_EDITOR(EditRotation3D, Q Math::Rotor3D& rot3) {
        width = GetRemWidth(width);

        auto [xrot, yrot, zrot] = rot3.EulerAngles();
        float xr = xrot.Degrees(), yr = yrot.Degrees(), zr = zrot.Degrees();
        DisplayTextCropped(title, GetItemRemainingWidth(width) - GetSpacingWidth());

        SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());

        const float w = (GetItemDefaultWidth(width) - 2 * GetSpacingWidth()) / 3;
        PushID(title.Data());
        EditScalarWithIcon((const char*)u8"θ:", COLOR_X_ANGLE, xr, 1, nullptr,              "%f°", w); SameLine();
        EditScalarWithIcon((const char*)u8"Ψ:", COLOR_Y_ANGLE, yr, 1, Q fRange { -90, 90 }, "%f°", w); SameLine();
        EditScalarWithIcon((const char*)u8"φ:", COLOR_Z_ANGLE, zr, 1, nullptr,              "%f°", w);
        PopID();

        rot3 = { Q Math::Degrees(xr),
                 Q Math::Degrees(yr),
                 Q Math::Degrees(zr) };
    }

    Q_IMGUI_EDITOR(EditYawPitch, float& yaw, float& pitch) {
        const float iw = (GetItemDefaultWidth(width) - GetSpacingWidth()) / 2;
        DisplayTextCropped(title, GetItemRemainingWidth(width) - GetSpacingWidth());
        SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());
        EditScalarWithIcon("Yaw",   COLOR_X_ANGLE, yaw,   0.01f, Q fRange { -Q Math::PI,             Q Math::PI }, {}, iw);
        SameLine();
        EditScalarWithIcon("Pitch", COLOR_Y_ANGLE, pitch, 0.01f, Q fRange { -Q Math::HALF_PI * 0.9f, Q Math::HALF_PI * 0.9f }, {}, iw);
    }

    template <class T, bool A>
    Q_IMGUI_EDITOR(EditColor, Q Math::IColor<T, A>& color) {
        width = GetRemWidth(width);
        DisplayTextCropped(title, GetItemRemainingWidth(width) - GetSpacingWidth());

        SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());
        const float fullWidth = GetItemDefaultWidth(width) - (float)color.Dimensions() * GetSpacingWidth() - GetFrameHeight(),
                    unitWidth = fullWidth / (float)color.Dimensions();

        static Q Math::fColor3 CHANNEL_COLORS[4] = { COLOR_X_AXIS, COLOR_Y_AXIS, COLOR_Z_AXIS, COLOR_ALPHA };
        for (Q usize i = 0; i < Q Math::IColor<T, A>::Dim; ++i) {
            const Q Range<T> range = { 0, T(Q Floating<T> ? 1 : 255) };
            PushID(title.Data());
            EditScalarWithIcon(&"R:\0G:\0B:\0A:"[i * 3], CHANNEL_COLORS[i], color[i],
                Q Floating<T> ? 0.005f : 1.0f, range, {}, unitWidth);
            SameLine();
            PopID();
        }

        PushID(title.Data(), "button");
        static constexpr Q u32 FLAGS = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreviewHalf;
        if constexpr (Q Floating<T>) {
            if constexpr (!A) {
                ColorEdit3("", color.Data(), FLAGS);
            } else {
                ColorEdit4("", color.Data(), FLAGS);
            }
        } else {
            Q Math::IColor<float, A> floatColor = (Q Math::IColor<float, A>)color;
            if constexpr (!A) {
                ColorEdit3("", floatColor.Data(), FLAGS);
            } else {
                ColorEdit4("", floatColor.Data(), FLAGS);
            }
            color = (Q Math::IColor<T, A>)floatColor;
        }
        PopID();
    }

    Q_IMGUI_EDITOR(EditTransform, Q Math::Transform2D& transform, float speed) {
        (void)width;
        if (!TreeNode(title.Data())) return;
        EditVector    ("Position", transform.pos, speed);
        EditVector    ("Scale",    transform.scale, speed);
        EditRotation2D("Rotation", transform.rot);
        TreePop();
    }

    Q_IMGUI_EDITOR(EditTransform, Q Math::Transform3D& transform, float speed) {
        (void)width;
        if (!TreeNode(title.Data())) return;
        EditVector    ("Position", transform.pos, speed);
        EditVector    ("Scale",    transform.scale, speed);
        EditRotation3D("Rotation", transform.rot);
        TreePop();
    }

    Q_IMGUI_EDITOR(EditCameraController, Q Graphics::CameraController3D& camera) {
        width = GetRemWidth(width);

        static bool showControls = false;

        if (!TreeNode(title.Data())) return;

        TextDisabled(camera.enabled ? " (press Esc to disable!)" : " (press Esc to enable!)");

        EditVector("Position", camera.position, 0.5f);
        EditYawPitch("Rotation", camera.yaw, camera.pitch);

        if (TreeNode("Controls")) {
            EditScalar("Speed", camera.speed, 0.5f);
            EditScalar("Sensitivity", camera.sensitivity, 0.01, Q fRange { 1 });
            EditScalar("FOV", camera.fov, 0.5, camera.fovRange);
            EditRange("FOV Range", camera.fovRange, 0.5f, Q fRange { 90.0f });

            {
                const float iw = (GetItemDefaultWidth(width) - GetSpacingWidth()) / 2;
                DisplayTextCropped("Zoom", GetItemRemainingWidth(width) - GetSpacingWidth());
                SameLine(0, GetItemRemainingWidth(width) - GetLastItemWidth());
                EditScalarWithIcon("Lerp",   COLOR_ALPHA, camera.smoothZoom, 0.01f, Q fRange { 1 }, {}, iw);
                SameLine();
                EditScalarWithIcon("Factor", COLOR_ALPHA, camera.zoomRatio,  0.01f, Q fRange { 1 }, {}, iw);

                bool sz = camera.UsesSmoothZoom();
                Checkbox("Use Smooth Zoom", &sz);
                if (sz != camera.UsesSmoothZoom()) camera.smoothZoom *= -1;
            }

            TreePop();
        }

        if (Button("Copy State to Clipboard")) {
            SetClipboardText(Quasi::Text::Format(
                "camera.position = fv3 {{{($),}}};\n"
                "camera.yaw = {}; camera.pitch = {};\n"
                "camera.speed = {};\n"
                "camera.sensitivity = {};\n"
                "camera.fov = {};\n"
                "camera.fovRange = {{ {}, {} }};\n"
                "camera.zoomRatio = {};\n"
                "camera.smoothZoom = {};\n\0",
                camera.position,
                camera.yaw, camera.pitch,
                camera.speed,
                camera.sensitivity,
                camera.fov,
                camera.fovRange.min, camera.fovRange.max,
                camera.zoomRatio,
                camera.smoothZoom)
            .Data());
        }
        SameLine();
        if (Button(showControls ? "Hide Controls" : "Show Controls")) {
            showControls ^= true;
        }
        if (showControls) {
            Begin("Camera Controls", &showControls);

            Text("[Esc] - Toggle Camera View");
            Text("Movement"); SameLine(); Separator();
            Text(
                "   [W]    + [Space]/[Shift]/[Ctrl]\n"
                "[A][S][D]    (up)   (down)  (speed up)\n"
            );
            Text("Zoom"); SameLine(); Separator();
            Text(
                "[Mouse] - Look around\n"
                "[Caps Lock] + [Scroll Wheel] - Zoom"
            );

            End();
        }

        TreePop();
    }

    Q_IMGUI_EDITOR(EditLight, Q Graphics::Light& light) {
        (void)width;
        Separator();
        if (!TreeNode(title.Data())) return;

        BeginTabBar("Light Edit");

        using namespace Q Math;
        using namespace Q Graphics;
        if (TabItemButton("Sun") && !light.Is<SunLight>())
            light.Set(SunLight {
                .direction = light.Direction()
            });
        if (TabItemButton("Point") && !light.Is<PointLight>())
            light.Set(PointLight {
                .position = light.Position(),
                .constant = 1.0f,
                .linear = 0.0f,
                .quadratic = 0.001f
            });
        if (TabItemButton("Spot") && !light.Is<FlashLight>()) {
            const auto [_, yaw, pitch] = light.Direction().SphericCoords();
            light.Set(FlashLight {
                .position = light.Position(),
                .yaw = yaw, .pitch = pitch,
                .innerCut = 12.5_deg, .outerCut = 20.0_deg
            });
        }

        EditColor("Color + Intensity", light.color);
        light.VisitMut(
            [](SunLight& sun) {
                auto [len, yaw, pitch] = sun.direction.SphericCoords();
                yaw   = std::isnan(*yaw)   ? 0.0_rad : yaw;
                pitch = std::isnan(*pitch) ? 0.0_rad : pitch;
                EditScalar("Yaw",    *yaw,   0.01, Q fRange { -PI,      PI });
                EditScalar("Pitch",  *pitch, 0.01, Q fRange { -HALF_PI, HALF_PI });
                EditScalar("Length", len, 0.1, Q fRange { 0, 10 });
                sun.direction = fv3::FromSpheric(len, yaw, pitch);
            },
            [](PointLight& point) {
                EditVector("Position", point.position);
                if (TreeNode("Light Attenuation")) {
                    EditScalar("Constant",  point.constant,  0.01f);
                    EditScalar("Linear",    point.linear,    0.01f);
                    EditScalar("Quadratic", point.quadratic, 0.01f);
                    TreePop();
                }
            },
            [](FlashLight& flash) {
                EditVector("Position", flash.position);

                flash.yaw   = std::isnan(*flash.yaw)   ? 0.0_rad : flash.yaw;
                flash.pitch = std::isnan(*flash.pitch) ? 0.0_rad : flash.pitch;
                EditScalar("Yaw",   *flash.yaw,   0.01, Q fRange { -PI,      PI });
                EditScalar("Pitch", *flash.pitch, 0.01, Q fRange { -HALF_PI, HALF_PI });

                EditScalar("Inner Cutoff", *flash.innerCut, 0.01, Q fRange { 0, PI });
                EditScalar("Outer Cutoff", *flash.outerCut, 0.01, Q fRange { 0, PI });
            }
        );

        EndTabBar();
        if (Button("Copy State to Clipboard")) {
            SetClipboardText(light.Visit<Quasi::String>(
                [&](const SunLight& sun) {
                    return Quasi::Text::Format(
                        "light = Graphics::SunLight {{\n"
                        "   .direction = fv3 {:($),},\n"
                        "}};\n"
                        "light.color = fColor {:($),};\n\0",
                        sun.direction,
                        light.color);
                },
                [&](const PointLight& point) {
                    return Quasi::Text::Format(
                        "light = Graphics::PointLight {{\n"
                        "   .position = fv3 {:($),},\n"
                        "   .constant = {},\n"
                        "   .linear = {},\n"
                        "   .quadratic = {},\n"
                        "}};\n"
                        "light.color = fColor {:($),};\n\0",
                        point.position,
                        point.constant, point.linear, point.quadratic,
                        light.color);
                },
                [&](const FlashLight& flash) {
                    return Quasi::Text::Format(
                        "light = Graphics::FlashLight {{\n"
                        "   .position = fv3 {{{($),}}},\n"
                        "   .yaw = {}, .pitch = {},\n"
                        "   .innerCut = {}, .outerCut = {}\n"
                        "}};\n"
                        "light.color = fColor {:($),};\n\0",
                        flash.position,
                        *flash.yaw, *flash.pitch,
                        *flash.innerCut, *flash.outerCut,
                        light.color);
                }
            ).Data());
        }
        TreePop();
    }

#pragma region Instantiations
    template ImGuiDataType ImGuiDataEnum<float> ();
    template ImGuiDataType ImGuiDataEnum<double>();
    template ImGuiDataType ImGuiDataEnum<Q u8 > ();
    template ImGuiDataType ImGuiDataEnum<Q i8 > ();
    template ImGuiDataType ImGuiDataEnum<Q u16> ();
    template ImGuiDataType ImGuiDataEnum<Q i16> ();
    template ImGuiDataType ImGuiDataEnum<Q u32> ();
    template ImGuiDataType ImGuiDataEnum<Q i32> ();
    template ImGuiDataType ImGuiDataEnum<Q u64> ();
    template ImGuiDataType ImGuiDataEnum<Q i64> ();

    template void EditScalar<float> (Q Str, float&,  float, Q NoInfer<Q Option<Q Range<float>>>,  float);
    template void EditScalar<double>(Q Str, double&, float, Q NoInfer<Q Option<Q Range<double>>>, float);
    template void EditScalar<Q u8 > (Q Str, Q u8 &,  float, Q NoInfer<Q Option<Q Range<Q u8 >>>,  float);
    template void EditScalar<Q i8 > (Q Str, Q i8 &,  float, Q NoInfer<Q Option<Q Range<Q i8 >>>,  float);
    template void EditScalar<Q u16> (Q Str, Q u16&,  float, Q NoInfer<Q Option<Q Range<Q u16>>>,  float);
    template void EditScalar<Q i16> (Q Str, Q i16&,  float, Q NoInfer<Q Option<Q Range<Q i16>>>,  float);
    template void EditScalar<Q u32> (Q Str, Q u32&,  float, Q NoInfer<Q Option<Q Range<Q u32>>>,  float);
    template void EditScalar<Q i32> (Q Str, Q i32&,  float, Q NoInfer<Q Option<Q Range<Q i32>>>,  float);
    template void EditScalar<Q u64> (Q Str, Q u64&,  float, Q NoInfer<Q Option<Q Range<Q u64>>>,  float);
    template void EditScalar<Q i64> (Q Str, Q i64&,  float, Q NoInfer<Q Option<Q Range<Q i64>>>,  float);

    template void EditVector<float, 2> (Q Str, Q Math::Vector<float, 2>&,  float, Q NoInfer<const Q Option<Q Math::Rect<float, 2>>&>,  float);
    template void EditVector<float, 3> (Q Str, Q Math::Vector<float, 3>&,  float, Q NoInfer<const Q Option<Q Math::Rect<float, 3>>&>,  float);
    template void EditVector<float, 4> (Q Str, Q Math::Vector<float, 4>&,  float, Q NoInfer<const Q Option<Q Math::Rect<float, 4>>&>,  float);
    template void EditVector<double, 2>(Q Str, Q Math::Vector<double, 2>&, float, Q NoInfer<const Q Option<Q Math::Rect<double, 2>>&>, float);
    template void EditVector<double, 3>(Q Str, Q Math::Vector<double, 3>&, float, Q NoInfer<const Q Option<Q Math::Rect<double, 3>>&>, float);
    template void EditVector<double, 4>(Q Str, Q Math::Vector<double, 4>&, float, Q NoInfer<const Q Option<Q Math::Rect<double, 4>>&>, float);
    template void EditVector<Q i32, 2> (Q Str, Q Math::Vector<Q i32, 2>&,  float, Q NoInfer<const Q Option<Q Math::Rect<Q i32, 2>>&>,  float);
    template void EditVector<Q i32, 3> (Q Str, Q Math::Vector<Q i32, 3>&,  float, Q NoInfer<const Q Option<Q Math::Rect<Q i32, 3>>&>,  float);
    template void EditVector<Q i32, 4> (Q Str, Q Math::Vector<Q i32, 4>&,  float, Q NoInfer<const Q Option<Q Math::Rect<Q i32, 4>>&>,  float);
    template void EditVector<Q u32, 2> (Q Str, Q Math::Vector<Q u32, 2>&,  float, Q NoInfer<const Q Option<Q Math::Rect<Q u32, 2>>&>,  float);
    template void EditVector<Q u32, 3> (Q Str, Q Math::Vector<Q u32, 3>&,  float, Q NoInfer<const Q Option<Q Math::Rect<Q u32, 3>>&>,  float);
    template void EditVector<Q u32, 4> (Q Str, Q Math::Vector<Q u32, 4>&,  float, Q NoInfer<const Q Option<Q Math::Rect<Q u32, 4>>&>,  float);
    template void EditVector<Q byte, 2>(Q Str, Q Math::Vector<Q byte, 2>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q byte, 2>>&>, float);
    template void EditVector<Q byte, 3>(Q Str, Q Math::Vector<Q byte, 3>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q byte, 3>>&>, float);
    template void EditVector<Q byte, 4>(Q Str, Q Math::Vector<Q byte, 4>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q byte, 4>>&>, float);

    template void EditRange<float> (Q Str, Q Range<float>&,  float, Q NoInfer<const Q Option<Q Range<float>>&>,  float);
    template void EditRange<double>(Q Str, Q Range<double>&, float, Q NoInfer<const Q Option<Q Range<double>>&>, float);
    template void EditRange<Q i32> (Q Str, Q Range<Q i32>&,  float, Q NoInfer<const Q Option<Q Range<Q i32>>&>,  float);
    template void EditRange<Q u32> (Q Str, Q Range<Q u32>&,  float, Q NoInfer<const Q Option<Q Range<Q u32>>&>,  float);
    template void EditRange<Q byte>(Q Str, Q Range<Q byte>&, float, Q NoInfer<const Q Option<Q Range<Q byte>>&>, float);

    template void EditRect<float, 2> (Q Str, Q Math::Rect<float, 2>&, float, Q NoInfer<const Q Option<Q Math::Rect<float, 2>>&>,  float);
    template void EditRect<float, 3> (Q Str, Q Math::Rect<float, 3>&, float, Q NoInfer<const Q Option<Q Math::Rect<float, 3>>&>,  float);
    template void EditRect<float, 4> (Q Str, Q Math::Rect<float, 4>&, float, Q NoInfer<const Q Option<Q Math::Rect<float, 4>>&>,  float);
    template void EditRect<double, 2>(Q Str, Q Math::Rect<double, 2>&,float, Q NoInfer<const Q Option<Q Math::Rect<double, 2>>&>, float);
    template void EditRect<double, 3>(Q Str, Q Math::Rect<double, 3>&,float, Q NoInfer<const Q Option<Q Math::Rect<double, 3>>&>, float);
    template void EditRect<double, 4>(Q Str, Q Math::Rect<double, 4>&,float, Q NoInfer<const Q Option<Q Math::Rect<double, 4>>&>, float);
    template void EditRect<Q i32, 2> (Q Str, Q Math::Rect<Q i32, 2>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q i32, 2>>&>,  float);
    template void EditRect<Q i32, 3> (Q Str, Q Math::Rect<Q i32, 3>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q i32, 3>>&>,  float);
    template void EditRect<Q i32, 4> (Q Str, Q Math::Rect<Q i32, 4>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q i32, 4>>&>,  float);
    template void EditRect<Q u32, 2> (Q Str, Q Math::Rect<Q u32, 2>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q u32, 2>>&>,  float);
    template void EditRect<Q u32, 3> (Q Str, Q Math::Rect<Q u32, 3>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q u32, 3>>&>,  float);
    template void EditRect<Q u32, 4> (Q Str, Q Math::Rect<Q u32, 4>&, float, Q NoInfer<const Q Option<Q Math::Rect<Q u32, 4>>&>,  float);
    template void EditRect<Q byte, 2>(Q Str, Q Math::Rect<Q byte, 2>&,float, Q NoInfer<const Q Option<Q Math::Rect<Q byte, 2>>&>, float);
    template void EditRect<Q byte, 3>(Q Str, Q Math::Rect<Q byte, 3>&,float, Q NoInfer<const Q Option<Q Math::Rect<Q byte, 3>>&>, float);
    template void EditRect<Q byte, 4>(Q Str, Q Math::Rect<Q byte, 4>&,float, Q NoInfer<const Q Option<Q Math::Rect<Q byte, 4>>&>, float);

    template void EditColor<float,  true >(Q Str, Q Math::fColor&,  float);
    template void EditColor<float,  false>(Q Str, Q Math::fColor3&, float);
    template void EditColor<Q byte, true >(Q Str, Q Math::uColor&,  float);
    template void EditColor<Q byte, false>(Q Str, Q Math::uColor3&, float);

    #pragma endregion
} // ImGui