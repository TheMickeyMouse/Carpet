#pragma once
#include "Body2D.h"

namespace Quasi::Physics2D {
    class World {
    public:
        Vec<Box<Body>> bodies;
        fv2 gravity;
    public:
        World() = default;
        World(const fv2& gravity) : gravity(gravity) {}
    public:
        usize BodyCount() const { return bodies.Length(); }
        void Reserve(usize size);
        void Clear();

        Body& CreateBody(const BodyCreateOptions& options, Shape shape);
        Body& CreatePolygon(const BodyCreateOptions& options, Span<const fv2> points);
        void DeleteBody(usize i);
        void DeleteBody(Ref<Body> body);

        void Update(float dt);
        void Update(float dt, int simUpdates);

        OptRef<Body> BodyAt(usize i);
        OptRef<const Body> BodyAt(usize i) const;
    };
} // Physics
