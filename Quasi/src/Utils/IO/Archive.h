#pragma once
#include "Utils/Span.h"
#include "Utils/HashMap.h"
#include "Utils/String.h"

namespace Quasi {
    class Archive {
        // static memory in application
        Bytes blob;
        HashMap<String, zRange> items;

        Archive() = default;
        Archive(Bytes data, HashMap<String, zRange> items) : blob(data), items(std::move(items)) {}

    public:
        static Archive New(u8* data, usize size, HashMap<String, zRange> items);
        static Archive FromPtrs(const char* const startEndPairs[], const char* const names[], usize numArgs);

        Bytes GetBytes() const;
        Option<Bytes> Get(Str resName) const;
        Bytes operator[](Str resName) const;

    private:
        static void WriteMangledName(Str name, Text::StringWriter dest);
        static void WriteVariableName(Str name, Text::StringWriter dest);
    public:
        static bool CheckReq();
        static void ArchiveFiles(Span<Str> filenames, Str resDir, Str curDir, Str archiveName, Text::StringWriter dest);
    };
} // Quasi