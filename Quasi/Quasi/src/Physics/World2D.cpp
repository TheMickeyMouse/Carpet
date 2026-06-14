#include "World2D.h"

#include "Utils/Algorithm.h"

namespace Quasi::Physics2D {
    void World::Reserve(usize size) {
        bodies.Reserve(size);
    }

    void World::Clear() {
        bodies.Clear();
    }

    Body& World::CreateBody(const BodyCreateOptions& options, Shape shape) {
        const float area = shape.ComputeArea();
        const bool isStatic = options.type == BodyType::STATIC;
        return *bodies.Push(Box<Body>::Build(
            options.position,
            Degrees(options.rotAngle),
            isStatic ? 0 : area * options.density,
            options.type,
            *this,
            std::move(shape)
        ));
    }

    Body& World::CreatePolygon(const BodyCreateOptions& options, Span<const fv2> points) {
        if (points.Length() <= 4) {
            StaticPolygonShape shape;
            shape.SetPointsUnsafe(points);
            const fv2 cen = shape.CalcCentroid();
            shape.FixCentroid(cen);
            Body& b = CreateBody(options, Shape(shape));
            b.position += cen;
            return b;
        } else {
            DynPolygonShape shape;
            shape.SetPointsUnsafe(points);
            const fv2 cen = shape.CalcCentroid();
            shape.FixCentroid(cen);
            Body& b = CreateBody(options, Shape(shape));
            b.position += cen;
            return b;
        }
    }

    void World::DeleteBody(usize i) {
        bodies.Pop(i);
    }

    void World::DeleteBody(Ref<Body> body) {
        const OptionUsize i = bodies.FindIf([=] (const Box<Body>& b) { return b.RefEquals(body); });
        if (!i) return;
        bodies.Pop(*i);
    }

    void World::Update(float dt) {
        for (Box<Body>& b : bodies) {
            if (!b->enabled) continue;

            if (b->type == BodyType::DYNAMIC)
                b->velocity += gravity * dt;
            b->Update(dt);
        }


        bodies.SortByKey([&] (const Box<Body>& b) { return b->boundingBox.min.x; });
        // std::ranges::sort(bodyIndicesSorted, [&](u32 i, u32 j) { return cmpr(bodies[i]) < cmpr(bodies[j]); });

        // sweep impl
        // std::vector<std::tuple<Body*, Body*, Collision::Event>> collisionPairs;
        Vec<Ref<Body>> active;
        for (Box<Body>& b : bodies) {
            if (!b->enabled) continue;
            const float min = b->boundingBox.min.x;
            for (u32 j = 0; j < active.Length();) {
                Body* c = active[j].Address();
                if (c->boundingBox.max.x > min) {
                    const bool bDyn = b->IsDynamic(), cDyn = c->IsDynamic();
                    if ((bDyn || cDyn) && c->boundingBox.RangeY().Overlaps(b->boundingBox.RangeY())) {
                        const Manifold manifold = b->CollideWith(*c);
                        if (manifold.contactCount && std::max(manifold.contactDepth[0], manifold.contactDepth[1]) > f32s::DELTA) {
                            b->TryCallTrigger(*c, EventType::HIT);
                            c->TryCallTrigger(*b, EventType::HIT);
                            StaticResolve (*b, *c, manifold);
                            DynamicResolve(*b, *c, manifold);
                            if (bDyn) b->TryUpdateTransforms();
                            if (cDyn) c->TryUpdateTransforms();
                        }
                    }
                    ++j;
                } else {
                    active.PopUnordered(j);
                }
            }
            active.Push(*b);
        }

        // for (const auto& [base, target, event] : collisionPairs) {
        //     StaticResolve (*base, *target, event);
        //     DynamicResolve(*base, *target, event);
        // }

        // for (uint i = 0; i < BodyCount(); ++i) {
        //     Body& base = bodies[i];
        //     fv2 prevPosition = base.position, prevVelocity = base.velocity;
        //     for (uint j = i + 1; j < BodyCount(); ++j) {
        //         Body& target = bodies[j];
        //         if (const Collision::Event event = base.CollideWith(target)) {
        //             if (event.Seperator().iszero()) continue;
        //             StaticResolve (base, target, event);
        //             DynamicResolve(base, target, event);
        //             if (outCollisions) outCollisions->emplace_back(event);
        //         }
        //     }
        //     base.simTime -= (prevPosition - base.position).len() / prevVelocity.len();
        // }
    }

    void World::Update(float dt, int simUpdates) {
        for (int i = 0; i < simUpdates; ++i) {
            Update(dt / (float)simUpdates);
        }
    }

    OptRef<Body> World::BodyAt(usize i) {
        return QGetterMut$(BodyAt, i);
    }

    OptRef<const Body> World::BodyAt(usize i) const {
        return i < bodies.Length() ? OptRefs::SomeRef(*bodies[i]) : nullptr;
    }
} // Physics