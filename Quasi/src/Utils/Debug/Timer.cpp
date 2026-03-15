#include "Timer.h"

#include "Logger.h"

namespace Quasi::Debug {
    Timer::~Timer() {
        Stop();
        Log();
    }

    DateTime Timer::Now() {
        return std::chrono::system_clock::now();
    }

    TimeDuration Timer::Instant() {
        return TimeDuration { 0 };
    }

    void Timer::Start() {
        paused = false;
        begin = Now();
    }

    TimeDuration Timer::Stop() {
        const auto now = Now();
        const auto dur = now - begin;
        paused = true;
        total += dur;
        return dur;
    }

    void Timer::Reset() {
        total = TimeDuration { 0 };
        paused = true;
    }

    TimeDuration Timer::TotalElapsed() const {
        return total;
    }

    void Timer::Log() {
        if (!outputLog) return;
        const u64 ns = TotalElapsedUnits<Nanosecond>();
        outputLog->QDebug$("{} timer elapsed {}.{:.03f}ms", name, ns / 1000, ns % 1000);
    }
} // Quasi