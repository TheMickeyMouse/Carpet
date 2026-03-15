#pragma once
#include <chrono>

#include "Utils/Ref.h"
#include "Utils/Str.h"

namespace Quasi::Debug {
    class Logger;

    using DateTime = std::chrono::time_point<std::chrono::system_clock>;
    using TimeDuration = std::chrono::duration<u64, std::ratio<1, 1'000'000'000>>;
    template <class Unit> using TimeUnit = std::chrono::duration<u64, Unit>;

    using Second      = std::ratio<1, 1>;
    using Millisecond = std::ratio<1, 1'000>;
    using Microsecond = std::ratio<1, 1'000'000>;
    using Nanosecond  = std::ratio<1, 1'000'000'000>;

    class Timer {
    public:
        DateTime begin;
        TimeDuration total;
        bool paused = false;
        Str name;
        OptRef<Logger> outputLog;

        Timer(Str name, OptRef<Logger> log = nullptr) : begin(Now()), total(0), name(name), outputLog(log) {}
        ~Timer();

        static DateTime Now();
        static TimeDuration Instant();

        template <class Unit> static u64 UnitConvert(TimeDuration d) {
            return std::chrono::duration_cast<TimeUnit<Unit>>(d).count();
        }

        void Start();
        TimeDuration Stop();
        void Resume() { return Start(); }
        void Reset();

        TimeDuration TotalElapsed() const;
        template <class Unit> u64 TotalElapsedUnits() const {
            return UnitConvert<Unit>(TotalElapsed());
        }

        void Log();
    };
} // Quasi
