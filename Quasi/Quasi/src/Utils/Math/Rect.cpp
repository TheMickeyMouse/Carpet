#include "Rect.h"

namespace Quasi::Math {
    template struct Rect<float,  2>;
    template struct Rect<float,  3>;
    template struct Rect<float,  4>;
    template struct Rect<double, 2>;
    template struct Rect<double, 3>;
    template struct Rect<double, 4>;
    template struct Rect<int,    2>;
    template struct Rect<int,    3>;
    template struct Rect<int,    4>;
    template struct Rect<uint,   2>;
    template struct Rect<uint,   3>;
    template struct Rect<uint,   4>;
}