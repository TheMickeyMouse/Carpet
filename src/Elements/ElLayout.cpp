#include "ElLayout.h"

namespace Carpet {
    QuadDir QuadDir::Inherit(const QuadDir& inherit) const {
        return {
            Els::Inherit(top,   inherit.top),
            Els::Inherit(right, inherit.right),
            Els::Inherit(btm,   inherit.btm),
            Els::Inherit(left,  inherit.left),
        };
    }

    ElLayout ElLayout::InheritFrom(const ElLayout& inheritLayout) const {
        return {
            .width   = Els::Inherit(width,  inheritLayout.width),
            .height  = Els::Inherit(height, inheritLayout.height),
            .padding = padding.Inherit(inheritLayout.padding),
            .margin  = margin.Inherit(inheritLayout.margin),
        };
    }

    void ElLayout::Resolve(const ElLayout& outerLayout) {
        // x-direction:
        // L-MARGIN L-PADDING WIDTH R-PADDING R-MARGIN
        if (Els::IsAuto(width)) {
            margin.left = Els::GetNum(margin.left, 0.0);
            margin.right = Els::GetNum(margin.right, 0.0);
            padding.left = Els::GetNum(padding.left, 0.0);
            padding.right = Els::GetNum(padding.right, 0.0);
            width = outerLayout.width - (outerLayout.padding.X() + margin.X());
        } else {
            float sizes[4] = { margin.left, padding.left, padding.right, margin.right };
            float totalSize = width; int numAutos = 0;
            for (const float x : sizes) {
                if (Els::IsNum(x)) totalSize += x;
                else ++numAutos;
            }
            const float autoSize = std::max(0.0f, (outerLayout.width - outerLayout.padding.X() - totalSize) / (float)numAutos);
            margin.left   = Els::GetNum(margin.left,   autoSize);
            margin.right  = Els::GetNum(margin.right,  autoSize);
            padding.left  = Els::GetNum(padding.left,  autoSize);
            padding.right = Els::GetNum(padding.right, autoSize);
        }

        if (Els::IsAuto(height)) {
            margin.top  = Els::GetNum(margin.top, 0.0);
            margin.btm  = Els::GetNum(margin.btm, 0.0);
            padding.top = Els::GetNum(padding.top, 0.0);
            padding.btm = Els::GetNum(padding.btm, 0.0);
            height = outerLayout.height - (outerLayout.padding.Y() + margin.Y());
        } else {
            float sizes[4] = { margin.top, padding.top, padding.btm, margin.btm };
            float totalSize = height; int numAutos = 0;
            for (const float x : sizes) {
                if (Els::IsNum(x)) totalSize += x;
                else ++numAutos;
            }
            const float autoSize = std::max(0.0f, (outerLayout.height - outerLayout.padding.Y() - totalSize) / (float)numAutos);
            margin.top  = Els::GetNum(margin.top,  autoSize);
            margin.btm  = Els::GetNum(margin.btm,  autoSize);
            padding.top = Els::GetNum(padding.top, autoSize);
            padding.btm = Els::GetNum(padding.btm, autoSize);
        }
    }
} // Carpet