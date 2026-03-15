#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    void Sphere::MergeImpl(Geometry3D::Batch batch) const {
        using namespace Math;
        const Rotor2D LAT_ROT = Radians(PI  / -(float)sections.y),
                      LON_ROT = Radians(TAU / (float)sections.x);

        Vec<fv3>& vs = batch.geometry.vertices, &ns = batch.geometry.normals;
        const usize tail = ns.Length();
        ns.Push({ 0, 1, 0 });

        Rotor2D pitch = Rotor2D::FromComplex({ 0, 1 });
        for (u32 lat = 0; lat < sections.y; ++lat) {
            Rotor2D yaw = {};
            for (u32 lon = 0; lon < sections.x; ++lon) {
                if (lat != 0) {
                    const fv3 pos = fv3::FromSpheric(1, yaw, pitch);
                    ns.Push(pos);
                    yaw += LON_ROT;
                }

                const u32 lon_1 = (lon + 1) % sections.x,
                          off = 1 + (lat - 1) * sections.x,
                          offNext = off + sections.x;
                if (lat == 0) {
                    batch.Tri(0, 1 + lon, 1 + lon_1);
                } else if (lat == sections.y - 1) {
                    batch.Tri(off + lon_1, off + lon, 1 + sections.x * (sections.y - 1));
                } else {
                    batch.Quad(off + lon, offNext + lon, offNext + lon_1, off + lon_1);
                }
            }
            pitch += LAT_ROT;
        }
        ns.Push({ 0, -1, 0 });

        for (const auto& n : ns.Skip(tail)) {
            vs.Push(radius * n);
        }
    }
}
