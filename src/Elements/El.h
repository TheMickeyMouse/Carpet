#pragma once
#include "ElLayout.h"
#include "ElMeta.h"
#include "Utils/PolyVec.h"
#include "Utils/Math/Color.h"

namespace Carpet {
    class GlassRenderer;
}

namespace Quasi::Graphics {
    class Canvas;
}

namespace Carpet {
    class El {
    public:
        OptRef<El> parent;
        PolyVec<El> children;
    protected:
        ElLayout overrideLayout, computedLayout;
        fv2 position; fv2 computedPosition;
        fColor background = {}, borderColor = {};
        float borderWidth = 5.0f, borderRadius = 0.0f;
    public:
        El() = default;
        virtual ~El() = default;
        virtual void Draw(Canvas& canvas);
        virtual void DrawGlass(GlassRenderer& glass) {}

        void DrawRecr(Canvas& canvas);
        void DrawGlassRecr(GlassRenderer& glass);

        void SetLayout(const ElLayout& layout);
        // returns TRUE if the layout is already DETERMINED; FALSE if layout isn't sure yet.
        void ComputeLayout(const ElLayout& inheritLayout, const fv2& parentPosition);

        Span<const Ref<El>> GetChildren() const;
        Span<Ref<El>> GetChildren();
        Span<const Ref<El>> GetSiblings() const;
        Span<Ref<El>> GetSiblings();

        using Self = El;
        static const ElMeta META;
        virtual const ElMeta& GetMeta() const { return META; }

        bool Set(Str fieldName, Str value);
    private:
        bool Set(const ElMeta& clsMeta, Str fieldName, Str value);
    public:

        void VisitChildren(FuncRef<void(El&)> visitor);
        void VisitRecursive(FuncRef<void(El&)> visitor);

        El& AddChild(Box<El> child);

        friend class UIDoc;
    };
} // Carpet