#pragma once
#include "Utils/Type.h"

namespace Quasi::Graphics {
	struct Triplet {
		u32 i, j, k;

		Triplet Add(u32 x) const { return { i + x, j + x, k + x }; }
		Triplet& Incr(u32 x) { i += x; j += x; k += x; return *this; }

		Triplet  operator+ (ConvTo<u32> auto x) const { return Add((u32)x); }
		Triplet& operator+=(ConvTo<u32> auto x) { return Incr((u32)x); }
	};
}