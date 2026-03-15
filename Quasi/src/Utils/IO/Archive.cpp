#include "Archive.h"

#include <filesystem>

#include "Utils/Debug/Logger.h"
#include "Utils/Iter/MapIter.h"

namespace Quasi {
    Archive Archive::New(u8* data, usize size, HashMap<String, zRange> items) {
        Archive arch { Bytes::Slice(data, size), std::move(items) };
        return arch;
    }

    Archive Archive::FromPtrs(const char* const startEndPairs[], const char* const names[], usize numArgs) {
        Archive archive;
        const u8* dataStart = (const u8*)startEndPairs[0], *dataEnd = (const u8*)startEndPairs[2 * numArgs - 1];
        for (usize i = 0; i < numArgs; i++) {
            const u8* start = (const u8*)startEndPairs[2 * i], *end = (const u8*)startEndPairs[2 * i + 1];
            archive.items.Insert(names[i], { (usize)(start - dataStart), (usize)(end - dataStart) });
        }
        archive.blob = Bytes::Slice(dataStart, dataEnd - dataStart);
        return archive;
    }

    Bytes Archive::GetBytes() const {
        return blob;
    }

    Option<Bytes> Archive::Get(Str resName) const {
        const auto dataRange = items.Get(resName);
        return dataRange ? Options::Some(blob.Subspan(*dataRange)) : nullptr;
    }

    Bytes Archive::operator[](Str resName) const {
        const auto dataRange = items.Get(resName);
        if (!dataRange) {
            Debug::QError$("couldn't find resource {}!", resName);
            return Bytes::Empty();
        }
        return blob.Subspan(*dataRange);
    }

    void Archive::WriteMangledName(Str name, Text::StringWriter dest) {
        for (char c : name) {
            dest.Write(Chr::IsAlphaNum(c) ? c : '_');
        }
    }

    void Archive::WriteVariableName(Str name, Text::StringWriter dest) {
        if (!name.IsEmpty() && !Chr::IsAlpha(name[0])) {
            dest.Write('_'); // prevents variables that start with '1' or stuff
        }
        dest.Write(name);
    }

    bool Archive::CheckReq() {
#ifdef _WIN32
#define CHECK_CMD_EXISTS(COMMAND) "where " COMMAND " > nul 2>&1"
#else
#define CHECK_CMD_EXISTS(COMMAND) "command -v " COMMAND " > /dev/null 2>&1"
#endif
        if (std::system(CHECK_CMD_EXISTS("ld"))) {
            Debug::QCritical$("ld doesn't exist in the system! Try installing MinGW");
            return false;
        }

        return true;
    }

    void Archive::ArchiveFiles(Span<Str> filenames, Str resDir, Str curDir, Str archiveName, Text::StringWriter dest) {
        // TODO: might have to sanitize filenames in the future but we aint worrying about that,
        // TODO: like no duplicate names (not considering _, -, +, ...)

        // write files to an object file
#ifdef _WIN32
#define CMD_MOVE "move"
#else
#define CMD_MOVE "mv"
#endif
        String inputFiles = String::Join(filenames.Iter().Map([] (Str f) { return f.Contains(' ') ? Text::Quote(f) : String(f); }), " ");
        String command = Text::Format("cd {0} && ld -r -b binary -o {1} {2} && " CMD_MOVE " {1} {3}",
            resDir, archiveName, inputFiles, curDir);
        Debug::QDebug$("running {}", command);
        command.AddNullTerm();
        std::system(command.Data());

        Vec<String> mangledNames;
        for (Str file : filenames) {
            mangledNames.Push("");
            WriteMangledName(file, Text::StringWriter::WriteTo(mangledNames.Last()));
        }

        dest << "namespace _ar {\n    extern char ";
        for (usize i = 0; i < mangledNames.Length(); i++) {
            const String& mname = mangledNames[i];
            WriteVariableName(mname, dest); dest << "_s[] asm(\"_binary_" << mname << "_start\"), ";
            WriteVariableName(mname, dest); dest << "_e[] asm(\"_binary_" << mname << "_end\")";
            if (i < mangledNames.Length() - 1) {
                dest << ", ";
            }
        }
        dest << ";\n    static constexpr const char* data_ptrs[] = {";
        for (usize i = 0; i < mangledNames.Length(); i++) {
            WriteVariableName(mangledNames[i], dest); dest << "_s, ";
            WriteVariableName(mangledNames[i], dest); dest << "_e, ";
        }
        dest << "}, *names[] = {";
        for (usize i = 0; i < mangledNames.Length(); i++) {
            dest << '\"' << filenames[i] << "\", ";
        }
        dest << "};\n}\n";

        dest << "#define FETCH_ARCHIVE() Archive::FromPtrs(_ar::data_ptrs, _ar::names, " << mangledNames.Length() << ")";
    }
} // Quasi