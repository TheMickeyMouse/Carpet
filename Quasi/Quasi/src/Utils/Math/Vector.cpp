#include "Vector.h"

namespace Quasi::Math {
    template struct Vector<int,    2>;
    template struct Vector<int,    3>;
    template struct Vector<int,    4>;
    template struct Vector<uint,   2>;
    template struct Vector<uint,   3>;
    template struct Vector<uint,   4>;
    template struct Vector<float,  2>;
    template struct Vector<float,  3>;
    template struct Vector<float,  4>;
    template struct Vector<double, 2>;
    template struct Vector<double, 3>;
    template struct Vector<double, 4>;

    VectorFormatter::FormatOptions VectorFormatter::ConfigureOptions(Str opt) {
        if (!opt.StartsWith('(')) return {};
        opt.Advance(1);

        OptionUsize captureEnd = opt.Find(')');
        if (!captureEnd) return {};

        FormatOptions options;
        options.elementFmt = opt.First(*captureEnd);
        options.separator = opt.Skip(*captureEnd + 1);
        return options;
    }
}
