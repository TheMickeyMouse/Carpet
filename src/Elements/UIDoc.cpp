#include "UIDoc.h"

namespace Carpet {
    void UIDoc::ComputeLayouts() {
        root.ComputeLayout({ dimensions.x, dimensions.y, 0, 0 }, { 300, 300 });

        Vec<Ref<El>> stack = Vecs::New({ Ref(root) });
        while (stack) {
            El& e = stack.Take();
            fv2 position = e.computedPosition;
            ElLayout layout = e.computedLayout;
            for (auto child : e.children) {
                child->ComputeLayout(layout, position);
                const float childHeight = child->computedLayout.OuterSize().y;
                position.y += childHeight;
                layout.height -= childHeight;
            }
            stack.Extend(e.children.RevIter());
        }
    }

    void UIDoc::Draw(Canvas& canvas) {
        root.DrawRecr(canvas);
    }

    void UIDoc::DrawGlass(GlassRenderer& glass) {
        root.DrawGlassRecr(glass);
    }

    bool UIDoc::Compile(Str src, OptRef<Debug::Logger> logger) {
#define RETERR(STR, ...) if (logger) logger->QError$("{}:{}: " STR, lineCount, i - lineStart __VA_OPT__(,) __VA_ARGS__); return false

        Ref current = root;
        usize last = 0;
        usize lineCount = 1, lineStart = 0;
        usize i = 0;
        Option<Str> property = nullptr;
        for (; i < src.Length(); ++i) {
            switch (src[i]) {
                // creating new element
                case '{': {
                    Str newElDecl = src[{ last, i }].AsStr();
                    newElDecl = newElDecl.Trim();
                    const OptRef elClass = ElMeta::Classes.Get(newElDecl);
                    if (!elClass) {
                        RETERR("element of type {} does not exist! did you mean: TODO?", newElDecl);
                    }
                    current = current->AddChild((*elClass)->CreateInstance());
                    last = i + 1;
                    break;
                }
                case '}': {
                    if (property) {
                        RETERR("unfinished property declaration! expected ';' for property '{}', but found '}}'!", *property);
                    }
                    OptRef parent = current->parent;
                    if (!parent) {
                        RETERR("extra closing brace '}}'!");
                    }
                    current = *parent;
                    last = i + 1;
                    break;
                }
                case ':': {
                    if (property) {
                        RETERR("unfinished property declaration! expected ';' for property '{}', but found ':'!", *property);
                    }
                    property = src[{ last, i }].AsStr().Trim();
                    last = i + 1;
                    break;
                }
                case ';': {
                    const Str propValue = src[{ last, i }].AsStr().Trim();
                    if (!property) {
                        RETERR("incomplete property declaration! no property assigned for the value '{}'", propValue);
                    }
                    if (!current->Set(*property, propValue)) {
                        RETERR("bad value for property '{}': found '{}'!", *property, propValue);
                    }
                    property = nullptr;
                    last = i + 1;
                    break;
                }
                case '\n': {
                    ++lineCount;
                    lineStart = i + 1;
                    break;
                }
                case '\'': [[fallthrough]]; case '"': {
                    bool foundEnd = false;
                    for (usize j = i + 1; j < src.Length(); ++j) {
                        if (src[j] == src[i]) {
                            foundEnd = true;
                            i = j;
                            break;
                        }
                    }
                    if (!foundEnd) {
                        RETERR("unclosed quotation mark <{}>! found EOF instead!", src[i]);
                    }
                    break;
                }
                default:;
            }
        }
        if (!current.RefEquals(root)) {
            RETERR("unclosed brace! expected '}}', but encountered EOF!");
        }
        return true;
    }
}
