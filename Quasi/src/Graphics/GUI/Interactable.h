#pragma once
#include "Utils/Math/Color.h"
#include "Utils/Math/Rect.h"

namespace Quasi {
    namespace Graphics {
        class Canvas;
    }

    namespace IO {
        class IO;
    }

    struct MouseEventType {
        enum E : int {
            NONE    = 0,
            ENTER   = 1,
            LEAVE   = 2,
            CLICK   = 4,
            RELEASE = 8,
        };
    };

    class Interactable {
    public:
        Math::fRect2D hitbox;
        int capturedEvents = ~0; // setting this to zero automatically disables it
        bool hovered = false, held = false, passthrough = false;

        Interactable() = default;
        Interactable(const Math::fRect2D& hitbox, int capturedEvents = ~0) : hitbox(hitbox), capturedEvents(capturedEvents) {}
        virtual ~Interactable() = default;
        virtual bool CaptureEvent(MouseEventType::E e, IO::IO& io);
    };

    class Clickable : public Interactable {
    public:
        FuncBox<void(MouseEventType::E e, IO::IO& io)> onClick = nullptr;

        Clickable() = default;
        Clickable(const Interactable& i, FuncBox<void(MouseEventType::E e, IO::IO& io)> onClick) : Interactable(i), onClick(std::move(onClick)) {}
        ~Clickable() override = default;

        Clickable(Clickable&&) = default;
        Clickable& operator=(Clickable&&) = default;

        bool CaptureEvent(MouseEventType::E e, IO::IO& io) override;
    };
}
