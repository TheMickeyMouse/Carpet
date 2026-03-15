#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    void Capsule::MergeImpl(Geometry3D::Batch batch) const {
        using namespace Math;
        const fv3 forward = (end - start).Norm();
        const Rotor3D orientUp = Rotor3D::OrientY(forward);
        const Matrix3x3 LON_ROT = Rotor3D::RotateAxis(forward, Radians(TAU / -(float)sections.x)).AsMatrixLinear(),
                        LAT_ROT = Rotor3D::RotateAxis(orientUp.KHat(), Radians(HALF_PI / -(float)sections.y)).AsMatrixLinear();

        batch.PushV(end + forward * radius, forward);
        fv3 pitchBase = forward;
        for (int lat = -(int)sections.y; lat < (int)sections.y; ++lat) {
            fv3 pos = pitchBase;
            for (u32 lon = 0; lon < sections.x; ++lon) {
                if (lat != -(int)sections.y) {
                    pos = LON_ROT * pos;
                    batch.PushV((lat < 0 ? end : start) + radius * pos, pos);
                }

                const u32 lon_1 = (lon + 1) % sections.x,
                          off = 1 + (lat + sections.y - 1) * sections.x,
                          offNext = off + sections.x;
                if (lat == -(int)sections.y) {
                    batch.Tri(0, 1 + lon, 1 + lon_1);
                } else if (lat == sections.y - 1) {
                    batch.Tri(off + lon_1, off + lon, 1 + sections.x * (2 * sections.y - 1));
                } else {
                    batch.Quad(off + lon, offNext + lon, offNext + lon_1, off + lon_1);
                }
            }
            pitchBase = LAT_ROT * pitchBase;
        }
        batch.PushV(start - forward * radius, -forward);
    }
}
