#pragma once
#include "Collision2D.h"

#include "Shape2D.h"
#include "Utils/Math/Vector.h"
#include "Utils/Math/Transform2D.h"

namespace Quasi::Physics2D {
    using namespace Math;
    
    enum class BodyType {
        STATIC,
        DYNAMIC,
        KINEMATIC,
        NUM,
        NONE = -1
    };

    class World;

    enum class EventType {
        HIT,
        ENTER,
        EXIT
    };

    using TriggerFn = FuncRef<void(const Body& self, const Body& other, EventType event)>;

    class Body {
    public:
        fv2 position, velocity;
        Rotor2D rotation; float angularVelocity = 0.0;
        float mass = 1.0f, invMass = 1.0f, inertia = 1.0f, invInertia = 1.0f;
        fRect2D baseBoundingBox;
        fRect2D boundingBox;
        BodyType type = BodyType::NONE;
        bool enabled = true;
        bool shapeHasChanged = true;

        Shape shape;
        Ref<World> world;
        TriggerFn trigger = nullptr;

        Body(const fv2& p, const Rotor2D& r, float m, BodyType type, World& world, Shape shape)
            : position(p), rotation(r), mass(m), invMass(m > 0 ? 1 / m : 0), type(type), shape(std::move(shape)),
              world(world) { TryUpdateTransforms(); }

        void AddVelocity       (const fv2& vel) { velocity += vel; }
        void AddMomentum       (const fv2& newtonSeconds);
        void AddAngularVelocity(float angVel) { angularVelocity += angVel; }
        void AddAngularMomentum(float angMomentum);

        void AddRelativeVelocity(const fv2& relPosition, const fv2& vel);
        void AddVelocityAt      (const fv2& absPosition, const fv2& vel);

        void SetMass(float newMass);

        void Stop() { velocity = 0; angularVelocity = 0; }

        Manifold CollideWith(const Body& target) const;
        Manifold CollideWith(const Shape& target, const Pose2D& xf) const;
        bool OverlapsWith(const Body& target) const;
        bool OverlapsWith(const Shape& target, const Pose2D& xf) const;
        Pose2D GetTransform() const;

        void Update(float dt);
        void TryUpdateTransforms();
        void SetShapeHasChanged();

        void SetTrigger(TriggerFn t);
        void TryCallTrigger(const Body& other, EventType event);

        bool IsStatic()  const { return type == BodyType::STATIC; }
        bool IsDynamic() const { return type == BodyType::DYNAMIC; }

        void Enable()  { enabled = true; }
        void Disable() { enabled = false; }

        fRect2D BoundingBox() const;

        friend class World;
        friend void StaticResolve (Body&, Body&, const Manifold&);
        friend void DynamicResolve(Body&, Body&, const Manifold&);
    };

    struct BodyCreateOptions {
        fv2 position {};
        float rotAngle = 0.0f;
        BodyType type = BodyType::DYNAMIC;
        float density = 1.0f;
    };
} // Physics2D
