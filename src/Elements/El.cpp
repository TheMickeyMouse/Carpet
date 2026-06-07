#include "El.h"

#include "GUI/Canvas.h"
#include "Utils/Math/Rect.h"

namespace Carpet {
    const ElMeta El::META = [] {
        ElMeta meta = ElMeta::NewClass<El, void>("El", &META);
        meta.AddField("width",    META_FSET(overrideLayout.width),   true);
        meta.AddField("height",   META_FSET(overrideLayout.height),  true);
        meta.AddField("padding",  META_FSET(overrideLayout.padding), true);
        meta.AddField("margin",   META_FSET(overrideLayout.margin),  true);
        meta.AddField("position", META_FSET(position), true);
        meta.AddField("background",  META_FSET(background));
        meta.AddField("borderColor", META_FSET(borderColor));
        meta.AddField("borderWidth", META_FSET(borderWidth));
        meta.AddField("borderRadius", META_FSET(borderRadius));
        return meta;
    } ();

    void El::Draw(Canvas& canvas) {
        canvas.StrokeWeight(borderWidth);
        canvas.Stroke(borderColor);
        canvas.Fill(background);
        canvas.DrawRoundedRect(fRect2D::FromSize(computedPosition, computedLayout.Size()), borderRadius);
    }

    void El::DrawRecr(Canvas& canvas) {
        Draw(canvas);
        for (auto child : children) {
            child->DrawRecr(canvas);
        }
    }

    void El::DrawGlassRecr(GlassRenderer& glass) {
        DrawGlass(glass);
        for (auto child : children) {
            child->DrawGlassRecr(glass);
        }
    }

    void El::SetLayout(const ElLayout& layout) {
        overrideLayout = layout;
    }

    void El::ComputeLayout(const ElLayout& inheritLayout, const fv2& parentPosition) {
        computedLayout = overrideLayout.InheritFrom(inheritLayout);
        computedLayout.Resolve(inheritLayout);
        computedPosition = position + parentPosition;
        computedPosition.x += computedLayout.margin.left + inheritLayout.padding.left;
        computedPosition.y += computedLayout.margin.top  + inheritLayout.padding.top;
    }

    Span<const Ref<El>> El::GetChildren() const {
        return children.AsSpan();
    }

    Span<Ref<El>> El::GetChildren() {
        return children.AsSpan();
    }

    Span<const Ref<El>> El::GetSiblings() const {
        return parent ? parent->GetChildren() : nullptr;
    }

    Span<Ref<El>> El::GetSiblings() {
        return parent ? parent->GetChildren() : nullptr;
    }

    bool El::Set(Str fieldName, Str value) {
        return Set(GetMeta(), fieldName, value);
    }

    bool El::Set(const ElMeta& clsMeta, Str fieldName, Str value) {
        OptRef<const ElMeta::Field> f = clsMeta.fields.Get(fieldName);
        if (!f) {
            return clsMeta.derivedClass ? Set(clsMeta.derivedClass, fieldName, value) : false;
        }
        return f->setter(this, value);
    }

    void El::VisitChildren(FuncRef<void(El&)> visitor) {
        for (auto child : children) {
            visitor(child);
        }
    }

    void El::VisitRecursive(FuncRef<void(El&)> visitor) {
        visitor(*this);
        for (auto child : children) {
            child->VisitRecursive(visitor);
        }
    }

    El& El::AddChild(Box<El> child) {
        El& el = children.Push(std::move(child));
        el.parent = *this;
        return el;
    }
}
