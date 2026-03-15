#include "Interactable.h"

namespace Quasi {
    bool Interactable::CaptureEvent(MouseEventType::E e, IO::IO& io) {
        if (e & MouseEventType::ENTER) hovered = true;
        if (e & MouseEventType::LEAVE) hovered = false;
        if (e & MouseEventType::CLICK) held = true;
        else if (e & MouseEventType::RELEASE) held = false;
        return passthrough;
    }

    bool Clickable::CaptureEvent(MouseEventType::E e, IO::IO& io) {
        const bool passthrough = Interactable::CaptureEvent(e, io);
        if (e & MouseEventType::CLICK) onClick(e, io);
        return passthrough;
    }
}
