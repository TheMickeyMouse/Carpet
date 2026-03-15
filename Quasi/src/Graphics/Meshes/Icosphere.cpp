#include "MeshBuilder.h"
#include "Utils/Algorithm.h"

namespace Quasi::Graphics::Meshes {
    void Icosphere::MergeImpl(Geometry3D::Batch batch) const {
#pragma region Icosahedron Data & Utils
        static constexpr u32 CORNER_COUNT = 12, EDGE_COUNT = 30, CENTER_COUNT = 20;
        static constexpr float NLEN = 1.90211'30325'90307f, // precomputed sqrt(1 + phi * phi)
                               I_1 = 1.0F / NLEN, I_PHI = Math::PHI / NLEN;

        static const Array IcoVert = Arrays::Of<Math::fv3>({
            // from https://en.wikipedia.org/wiki/Regular_icosahedron#Construction
            { 0, +I_1, +I_PHI },
            { 0, -I_1, +I_PHI },
            { 0, +I_1, -I_PHI },
            { 0, -I_1, -I_PHI },
            { +I_1, +I_PHI, 0 },
            { -I_1, +I_PHI, 0 },
            { +I_1, -I_PHI, 0 },
            { -I_1, -I_PHI, 0 },
            { +I_PHI, 0, +I_1 },
            { +I_PHI, 0, -I_1 },
            { -I_PHI, 0, +I_1 },
            { -I_PHI, 0, -I_1 },
        });

        static constexpr u8 ICO_EDGES[EDGE_COUNT] {
            0x01, 0x04, 0x05, 0x08, 0x0A, 0x16,
            0x17, 0x18, 0x1A, 0x23, 0x24, 0x25,
            0x29, 0x2B, 0x36, 0x37, 0x39, 0x3B,
            0x45, 0x48, 0x49, 0x5A, 0x5B, 0x67,
            0x68, 0x69, 0x7A, 0x7B, 0x89, 0xAB,
        };
        static constexpr auto FindEdge = [] (u8 p) { return Span { ICO_EDGES }.LowerBound(p); };

        u32 faceIdx = 0;
        static constexpr Array<Triplet, CENTER_COUNT> ICO_FACES { {
            { 0, 1, 8 },  { 0, 1, 10 }, { 2, 3,  9 },   { 2, 3,  11 },
            { 4, 8, 9 },  { 6, 8, 9 },  { 5, 10, 11 },  { 7, 10, 11 },
            { 0, 4, 8 },  { 1, 6, 8 },  { 2, 4,  9 },   { 3, 6,  9 },
            { 0, 5, 10 }, { 1, 7, 10 }, { 2, 5,  11 },  { 3, 7,  11 },
            { 0, 4, 5 },  { 2, 4, 5 },  { 1, 6,  7 },   { 3, 6,  7 },
        } };
        static const auto Face = [&] { return ICO_FACES[faceIdx]; };

        const u32 EDGE_V_COUNT   = divisions - 1;
        const u32 CENTER_V_COUNT = (divisions - 2) * (divisions - 1) / 2;

        static const auto EdgeIdx = [&] (u32 e, u32 d) -> u32 { return CORNER_COUNT + e * EDGE_V_COUNT + d; };
        static const auto FaceIdx = [&] (u32 f, u32 p, u32 q) -> u32 {
            return CORNER_COUNT + EDGE_COUNT * EDGE_V_COUNT + f * CENTER_V_COUNT + (p - 2) * (p - 1) / 2 + (q - 1);
        };

        static const auto IndexOf = [&] (u32 p, u32 q) -> u32 {
            if (p == 0 && q == 0) return Face().i;
            if (p == divisions && q == 0) return Face().j;
            if (p == divisions && q == divisions) return Face().k;
            if (q == 0 || q == p || p == divisions) { // edge
                const bool isSide = p == divisions;
                const u32 lineStart = isSide ? Face().j : Face().i,
                          lineEnd = q ? Face().k : Face().j,
                          edgeIdx = FindEdge((lineStart << 4) + lineEnd);
                return EdgeIdx(edgeIdx, (isSide ? q : p) - 1);
            }
            return FaceIdx(faceIdx, p, q);
        };
#pragma endregion

        // FUTURE ME LOOKING AT THIS:
        // I HAVE NO IDEA WHAT IS GOING ON.
        // INSANE AMOUNTS OF MATH IS GETTING EXECUTED;
        // PAST ME WAS PROBABLY ON SOME CRACK WHILE WRITING THIS
        // BUT SINCE IT WORKS DONT CHANGE IT. EVER!!!!

        using namespace Math;

        // we can calculate vertices later by r * n, since its a ball
        Vec<fv3>& vs = batch.geometry.vertices, &normals = batch.geometry.normals;
        const usize V_COUNT = CORNER_COUNT + EDGE_V_COUNT * EDGE_COUNT + CENTER_V_COUNT * CENTER_COUNT;
        normals.ResizeExtra(V_COUNT);
        vs.Reserve(V_COUNT);

        Span<fv3> ns = normals.Skip(normals.Length() - V_COUNT);

        // inital 12 vertices
        for (u32 i = 0; i < CORNER_COUNT; ++i)
            ns[i] = IcoVert[i];

        for (; faceIdx < CENTER_COUNT; ++faceIdx) {
            // loops through a triangle, p = 1 to prevent the (0,0) coordinate
            for (u32 p = 1; p <= divisions; ++p) {
                for (u32 q = 0; q <= p; ++q) {
                    if (p == divisions && (q == 0 || q == divisions)) continue;
                    if (q == 0 || q == p || p == divisions) { // edge, interpolate between 2 points
                        const bool isSide = p == divisions;

                        const u32 lineStart = isSide ? Face().j : Face().i,
                                  lineEnd = q ? Face().k : Face().j,
                                  edgeIdx = FindEdge((lineStart << 4) + lineEnd),
                                  dist = isSide ? q : p,
                                  idx = EdgeIdx(edgeIdx, dist - 1);

                        const float factor = (float)dist / (float)divisions;
                        const fv3 pos = (IcoVert[lineStart] * (1.0f - factor) + IcoVert[lineEnd] * factor).Norm();

                        ns[idx] = pos;
                        continue;
                    }
                    // center, interpolate between 3 points
                    const fv3 pos = (IcoVert[Face().i] * ((float)(divisions - p) / (float)divisions)
                                   + IcoVert[Face().j] * ((float)(p - q)         / (float)divisions)
                                   + IcoVert[Face().k] * ((float)q               / (float)divisions)).Norm();
                    const u32 idx = IndexOf(p, q);
                    ns[idx] = pos;
                }
            }
            // the indices (this is an orientation adjustment ccw -> cw for certain faces)
            const bool iSwap = (faceIdx % 4 == 1 || faceIdx % 4 == 2) ^ (8 <= faceIdx && faceIdx < 12);
            for (u32 p = 0; p < divisions; ++p) {
                for (u32 q = 0; q < p; ++q) {
                    const u32 p1 = IndexOf(p, q);
                    batch.Tri(p1, IndexOf(p + 1, q + !iSwap), IndexOf(p + 1, q + iSwap));
                    batch.Tri(p1, IndexOf(p + iSwap, q + 1),  IndexOf(p + !iSwap, q + 1));
                }
                batch.Tri(IndexOf(p, p), IndexOf(p + 1, p + !iSwap), IndexOf(p + 1, p + iSwap));
            }
        }
        for (const auto& n : ns) {
            vs.Push(radius * n);
        }
    }
}
