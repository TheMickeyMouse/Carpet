#include "StringWriter.h"

#include <cstdio>

#include "Utils/String.h"
#include "Utils/Text.h"

namespace Quasi::Text {
    StringWriter StringWriter::WriteTo(String& string) {
        return { FuncRefs::FromRaw(&string, StringWriteCallback) };
    }

    StringWriter StringWriter::WriteToFile(std::FILE* file) {
        return { FuncRefs::FromRaw(file, FileWriteCallback) };
    }

    StringWriter StringWriter::WriteToConsole() {
        return WriteToFile(stdout);
    }

    StringWriter StringWriter::WriteToError() {
        return WriteToFile(stderr);
    }

    void StringWriter::StringWriteCallback(void* s, Str str) {
        ((String*)s)->AppendStr(str);
    }

    void StringWriter::FileWriteCallback(void* file, Str str) {
        std::fwrite(str.Data(), 1, str.Length(), (std::FILE*)file);
    }

    usize StringWriter::Write(Str str) {
        writer(str);
        return str.Length();
    }

    usize StringWriter::Write(char c) {
        writer(Str::Slice(&c, 1));
        return 1;
    }

    usize StringWriter::WriteRepeat(char c, usize n) {
        const u64 repeated8bytes = c * 0x0101'0101'0101'0101;
        const Str rep8 = Str::Slice((const char*)&repeated8bytes, 8);
        for (; n > 8; n -= 8) {
            Write(rep8);
        }
        Write(rep8.Substr(0, n));
        return n;
    }

    usize StringWriter::SetColor(ConsoleColor col) {
        return Text::FormatObjectTo(*this, col, Str::Empty());
    }
}
