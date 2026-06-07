#include "ElMeta.h"
#include "El.h"

namespace Carpet {
    HashMap<String, Ref<const ElMeta>> ElMeta::Classes = {};

    void ElMeta::RegisterClass(const ElMeta& classMeta) {
        Classes.Insert(classMeta.clsName, classMeta);
    }

    Box<El> ElMeta::CreateInstance() const {
        return constructor();
    }

    void ElMeta::AddField(Str name, FuncPtr<bool, El*, Str> setter, bool affectsLayout) {
        fields.Insert(name, { name, setter, affectsLayout });
    }
} // Carpet