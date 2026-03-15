#include "Logger.h"

#include <chrono>
#include "internal_debug_break.h"
#include "Utils/Text.h"

namespace Quasi::Debug {
    Logger Logger::InternalLog = [] {
        Logger::WinEnableANSI();

        Logger log { Text::StringWriter::WriteToConsole() };
        log.SetName("Internal");

        log.SetBreakLevel(Severity::ERROR);
        log.SetShortenFile(true);
        log.SetIncludeFunc(false);
        log.SetLocPad(0);
        return log;
    }();

    Logger& Logger::GetInternalLog() {
        return InternalLog;
    }

    void DebugBreak() {
        if constexpr (Logger::DEBUG)
            debug_break();
    }

    void Logger::FmtLog(Text::StringWriter output, const LogEntry& log) const {
        return FmtLog(output, log.log, log.severity, log.time, log.fileLoc);
    }

    void Logger::FmtLog(Text::StringWriter output, Str log, Severity::E severity, DateTime time, const SourceLoc& fileLoc) const {
        const auto [scol, sname] = Severity::NAMES[severity];
        Text::FormatTo(output,
            "{}[{:%y-%M-%d %H:%m:%s.%u}]{} {}> {}{:<8}",
            scol, time, Text::RESET, name,
            scol, Text::Format("[{}]:", sname)
        );
        FmtSourceLoc(output, fileLoc);
        output.Write(log);
        output.SetColor(Text::RESET);
        output.Write('\n');
        fflush(stdout);
    }

    Str Logger::FmtFile(Str fullname) const {
        return shortenFileNames ? Text::SplitDirectory(fullname)[2_nd] : fullname;
    }

    void Logger::FmtSourceLoc(Text::StringWriter output, const SourceLoc& loc) const {
        includeFunction ?
            FormatTo(output, "{}:{}:{} in {}: ", FmtFile(loc.file_name()), loc.line(), loc.column(), loc.function_name()) :
            FormatTo(output, "{}:{}:{}: ", FmtFile(loc.file_name()), loc.line(), loc.column());
    }

    void Logger::LogNoOut(const Severity::E sv, const Str s, const SourceLoc& loc) {
        if (recordLogs)
            logs.Push(LogEntry { String { s }, sv, Timer::Now(), loc });
    }

    void Logger::ConsoleLog(const Severity::E sv, const Str s, const SourceLoc& loc) {
        FmtLog(logOut, s, sv, Timer::Now(), loc);
    }

    void Logger::Log(const Severity::E sv, const Str s, const SourceLoc& loc) {
        LogNoOut(sv, s, loc);
        ConsoleLog(sv, s, loc);
        if (Overrides(breakLevel, sv)) {
            DebugBreak();
        }
    }

    void Logger::AssertMsg(const bool assert, Str msg, const SourceLoc& loc) {
        if (!assert) {
            Log(Severity::ERROR, Text::Format("Assertion failed: {}", msg), loc);
            DebugBreak();
        }
    }

    void Logger::WriteAllLogs(Text::StringWriter out, Severity::E filter) {
        for (const LogEntry& entry : logs) {
            if (Overrides(filter, entry.severity))
                FmtLog(out, entry);
        }
    }
}

namespace Quasi::Text {
    usize Formatter<std::chrono::time_point<std::chrono::system_clock>>::FormatTo(StringWriter out,
        const Debug::DateTime& time, Str fmt) {
        const auto d = floor<std::chrono::days>(time);
        const std::chrono::year_month_day ymd = d;
        const std::chrono::hh_mm_ss       hms { round<std::chrono::milliseconds>(time - d) };
        constexpr Str MONTH_NAMES[] = {
            "January"_str,
            "Febuary"_str,
            "March"_str,
            "April"_str,
            "May"_str,
            "June"_str,
            "July"_str,
            "August"_str,
            "September"_str,
            "October"_str,
            "November"_str,
            "December"_str,
        };
        constexpr Str WEEKDAY_NAMES[] = {
            "Monday"_str,
            "Tuesday"_str,
            "Wednesday"_str,
            "Thurday"_str,
            "Friday"_str,
            "Satarday"_str,
            "Sunday"_str,
        };
        using std::chrono::operator ""h;
        usize len = 0;
        for (u32 i = 0; i < fmt.Length(); ++i) {
            if (fmt[i] != '%') {
                out.Write(fmt[i]);
                ++len;
                continue;
            }
            switch (fmt[i + 1]) {
                case '%': out.Write('%'); ++len; ++i; continue;
                case 'y': len += FormatObjectTo(out, (i32)ymd.year());                   ++i; continue;
                case 'M': len += Text::FormatTo(out, "{:02}", (u32)ymd.month());         ++i; continue;
                case 'N': len += out.Write(MONTH_NAMES[(u32)ymd.month()]);               ++i; continue;
                case 'n': len += out.Write(MONTH_NAMES[(u32)ymd.month()].First(3));      ++i; continue;
                case 'd': len += Text::FormatTo(out, "{:02}", (u32)ymd.day());           ++i; continue;
                case 'A': len += out.Write(WEEKDAY_NAMES[(u32)ymd.day()]);               ++i; continue;
                case 'a': len += out.Write(WEEKDAY_NAMES[(u32)ymd.day()].First(3));      ++i; continue;
                case 'h': len += Text::FormatTo(out, "{:02}", hms.hours().count() % 12); ++i; continue;
                case 'H': len += Text::FormatTo(out, "{:02}", hms.hours().count());      ++i; continue;
                case 'g': len += out.Write(hms.hours() >= 12h ? "PM"_str : "AM"_str);    ++i; continue;
                case 'm': len += Text::FormatTo(out, "{:02}", hms.minutes().count());    ++i; continue;
                case 's': len += Text::FormatTo(out, "{:02}", hms.seconds().count());    ++i; continue;
                case 'u': len += Text::FormatTo(out, "{:03}", hms.subseconds().count()); ++i; continue;
                default:;
            }
        }
        return len;
    }
}

#include <windows.h>

void Quasi::Debug::Logger::WinEnableANSI() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hConsole, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);
}
