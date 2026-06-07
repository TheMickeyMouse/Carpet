#pragma once
#include "../Common.h"
#include "Utils/Math/Rect.h"
#include "Utils/Math/Vector.h"

namespace Carpet {
    struct Els {
        enum { _INHERIT_PAYLOAD = 3, _AUTO_PAYLOAD, _FIT_PAYLOAD };
        static constexpr float INHERIT = f32s::QNaN(_INHERIT_PAYLOAD);
        static constexpr float AUTO    = f32s::QNaN(_AUTO_PAYLOAD);
        static bool IsInherit(float x) { return f32s::QNaNPayload(x) == _INHERIT_PAYLOAD; }
        static bool IsAuto(float x) { return f32s::QNaNPayload(x) == _AUTO_PAYLOAD; }
        static bool IsNum(float x) { return !f32s::IsNaN(x); }
        static float GetNum(float x, float def) {
            return IsNum(x) ? x : def;
        }
        static float Inherit(float value, float inherited) {
            return IsInherit(value) ? inherited : value;
        }
        // adds values but propagates AUTO.
        static float AddAutos(float x, float y) {
            const float sum = x + y;
            return IsNum(sum) ? sum : AUTO;
        }

        // assumes remSpace is NOT AUTO. returns remaining space = remspace - left - right
        // static float ResolveSpace(float remSpace, float& left, float& right) {
        //     if (IsAuto(left)) {
        //         if (IsAuto(right)) {
        //             // auto WIDTH auto case: split evenly
        //             left = right = remSpace / 2.0f;
        //             return 0;
        //         } else {
        //             // auto WIDTH FIXED case: left = space - right
        //             right = std::min(right, remSpace);
        //             left = remSpace - right;
        //             return 0;
        //         }
        //     } else {
        //         if (IsAuto(right)) {
        //             // FIXED WIDTH auto case: right = space - left
        //             left = std::min(left, remSpace);
        //             right = remSpace - left;
        //             return 0;
        //         }
        //         return remSpace - left - right;
        //     }
        // }
    };

    struct QuadDir {
        float top, right, btm, left;
        QuadDir() : QuadDir(0.0f, 0.0f, 0.0f, 0.0f) {}
        QuadDir(float t, float r, float b, float l = 0.0f) : top(t), right(r), btm(b), left(l) {}
        QuadDir(float y, float x) : QuadDir(y, x, y, x) {}
        QuadDir(float x) : QuadDir(x, x, x, x) {}

        QuadDir Inherit(const QuadDir& inherit) const;
        float X() const { return right + left; }
        float Y() const { return top + btm; }
        fv2 TotalSize() const { return { X(), Y() }; }
        fv2 TopLeft() const { return { left, top }; }
    };

    struct ElLayout {
        float width = Els::AUTO, height = Els::AUTO;
        QuadDir padding;
        QuadDir margin;

        fv2 Size() const { return { width, height }; }
        fv2 InnerSize() const { return Size() - padding.TotalSize(); }
        fv2 OuterSize() const { return Size() + margin.TotalSize(); }

        ElLayout InheritFrom(const ElLayout& inheritLayout) const;
        void Resolve(const ElLayout& outerLayout);
    };
} // Carpet