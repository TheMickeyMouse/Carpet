#pragma once
#include "ElLayout.h"
#include "../Common.h"
#include "Utils/HashMap.h"
#include "Utils/String.h"
#include "Utils/Math/Color.h"

namespace Carpet {
    class El;

    // struct Any {
    //     std::type_index type;
    //     const void* value;
    //
    //     template <class T> const T& Get() const {
    //         return *(const T*)value;
    //     }
    //     template <class T> OptRef<const T> TryGet() const {
    //         return type == typeid(T) ? Get<T>() : nullptr;
    //     }
    // };

    struct ElValue {
        template <class T> static Option<T> Parse(Str x) { return nullptr; }
    };
    template <> inline Option<float>   ElValue::Parse<float> (Str x) { return Text::Parse<float>(x); }
    template <> inline Option<fColor>  ElValue::Parse<fColor>(Str x) { return fColor::FromHex(x); }
    template <> inline Option<fv2>     ElValue::Parse<fv2>   (Str x) { return fv2::Parse(x, " "); }
    template <> inline Option<String>  ElValue::Parse<String>(Str x) {
        if ((!x.StartsWith('"')  || !x.EndsWith('"')) &&
            (!x.StartsWith('\'') || !x.EndsWith('\''))) return nullptr;
        return x.Substr(1, x.Length() - 2).Unescape();
    }
    template <> inline Option<QuadDir> ElValue::Parse<QuadDir>(Str x) {
        float sides[4] = {};
        int i = 0;
        for (; i < 4; ++i) {
            if (x.IsEmpty()) break;
            const auto [first, rest] = x.SplitOnce(' ');
            Option s = Text::Parse<float>(first); if (!s) return nullptr;
            sides[i] = *s;
            x = rest;
        }
        switch (i) {
            case 1: return QuadDir { sides[0] };
            case 2: return QuadDir { sides[0], sides[1] };
            case 3: return QuadDir { sides[0], sides[1], sides[2] };
            case 4: return QuadDir { sides[0], sides[1], sides[2], sides[3] };
            default: return nullptr;
        }
    }

    // a description of an 'el' subclass
    struct ElMeta {
        struct Field {
            // this is technically duplicating info but whatever
            String name;
            FuncPtr<bool, El*, Str> setter;
            bool affectsLayout;
        };
        String clsName;
        HashMap<String, Field> fields = {};
        FuncPtr<Box<El>> constructor = nullptr;
        OptRef<const ElMeta> derivedClass = nullptr;

        template <class T, class Base>
        static ElMeta NewClass(Str clsName, const ElMeta* address) {
            ElMeta meta = { .clsName = clsName, .constructor = [] () -> Box<El> { return Box<T>::Build(); } };
            if constexpr (!SameAs<Base, void>) {
                meta.derivedClass = Base::META;
            }
            RegisterClass(*address);
            return meta;
        }

        static HashMap<String, Ref<const ElMeta>> Classes;
        static void RegisterClass(const ElMeta& classMeta);

        Box<El> CreateInstance() const;

        void AddField(Str name, FuncPtr<bool, El*, Str> setter, bool affectsLayout = false);

#define META_FSET(EXPR) [] (El* el, Str val) { \
    using T = decltype(Self {}.EXPR); \
    Self* subEl = dynamic_cast<Self*>(el); if (!subEl) return false; \
    Option value = ElValue::Parse<T>(val); if (!value) return false; \
    subEl->EXPR = value.Unwrap(); \
    return true; \
}
    };
} // Carpet