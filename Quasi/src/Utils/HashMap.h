#pragma once
#include "Hash.h"
#include "Utils/Debug/Logger.h"

// ported from robin_hood's hashmap implementation
// https://github.com/martinus/robin-hood-hashing
namespace Quasi {
    namespace Memory {
        // allocates bulks of memory for objects of type T.
        // uses linked list to keep track of all usable memory,
        // as well as cleaning up previously allocated memory in listToFree.
        // overhead per allocation is the size of a pointer.
        template <class T, usize MinNumAllocs = 4, usize MaxNumAllocs = 256>
        struct BulkPoolAllocator {
        private:
            // enforce byte alignment of the T's
            static constexpr usize ALIGNMENT = alignof(T) > alignof(T*) ? alignof(T) : alignof(T*);
            static constexpr usize ALIGNED_SIZE = ((sizeof(T) - 1) / ALIGNMENT + 1) * ALIGNMENT;

            static_assert(MaxNumAllocs >= MinNumAllocs && MinNumAllocs > 0);

            using LinkedListPtr = u8*;
            // memory that hasn't been used yet
            LinkedListPtr usableMemory = nullptr;
            // memory that hasn't been freed yet
            LinkedListPtr listToFree = nullptr;
        public:
            BulkPoolAllocator() = default;

            BulkPoolAllocator(const BulkPoolAllocator&) = delete;
            BulkPoolAllocator& operator=(const BulkPoolAllocator&) = delete;

            BulkPoolAllocator(BulkPoolAllocator&& pa) noexcept :
                usableMemory(pa.usableMemory), listToFree(pa.listToFree) {
                pa.usableMemory = nullptr;
                pa.listToFree = nullptr;
            }

            BulkPoolAllocator& operator=(BulkPoolAllocator&& pa) noexcept {
                Reset();
                new(this) BulkPoolAllocator(std::move(pa));
                return *this;
            }

            ~BulkPoolAllocator() {
                Reset();
            }

            // Deallocates all allocated memory.
            void Reset() {
                while (listToFree) {
                    const LinkedListPtr next = Next(listToFree);
                    FreeRaw(listToFree);
                    listToFree = next;
                }
                usableMemory = nullptr;
            }

            // allocates uninitalized memory. use placement new to initialize objects
            T* Allocate() {
                T* tmp = (T*)usableMemory;
                if (!tmp)
                    tmp = PerformAllocation();
                usableMemory = Next(tmp);
                return tmp;
            }

            // does not actually deallocate nor call the destructor but puts it back in usable memory
            void Deallocate(T* obj) {
                Next(obj) = usableMemory;
                usableMemory = obj;
            }

            // adds memory to the allocator unless there aren't enough bytes to make use of
            void AddIfEnough(void* ptr, usize bytes) {
                // calculate number of available elements in ptr
                if (bytes < ALIGNMENT + ALIGNED_SIZE) {
                    // not enough data for at least one element.
                    FreeRaw(ptr);
                } else {
                    Add(ptr, bytes);
                }
            }
        private:
            static LinkedListPtr& Next(LinkedListPtr list) {
                // turns the current node into an address to the next item, then dereferencing
                return *Memory::TransmutePtr<LinkedListPtr>(list);
            }

            // calculates amt. of memory to allocate next, without storing to save 1 int
            usize ShouldAllocNum() const {
                T** l = listToFree;
                usize numAllocs = MinNumAllocs;

                while (numAllocs * 2 <= MaxNumAllocs && l) {
                    l = Next(l);
                    numAllocs *= 2;
                }
                return numAllocs;
            }

            // adds memory to the allocator by concating it to listToFree and usableMemory
            void Add(void* newData, const usize numBytes) {
                const usize numElements = (numBytes - ALIGNMENT) / ALIGNED_SIZE;

                const LinkedListPtr data = (LinkedListPtr)newData;

                // record data onto the list to free, concating lists
                Next(data) = listToFree;
                listToFree = data;

                // create linked list for newly allocated data,
                // skipping 1 pointer ahead used to keep track of listToFree
                const LinkedListPtr headOfT = (LinkedListPtr)((u8*)newData + ALIGNMENT);
                u8* h = headOfT;

                // makes trivial linked list, each node pointing to the next
                for (usize i = 0; i < numElements; ++i) {
                    Next(h + i * ALIGNED_SIZE) = h + (i + 1) * ALIGNED_SIZE;
                }

                // last one points to null, indicating end of list
                Next(h + (numElements - 1) * ALIGNED_SIZE) = usableMemory;
                usableMemory = headOfT;
            }

            // called when no memory is available (head == nullptr)
            T* PerformAllocation() {
                const usize numAlloc = ShouldAllocNum();

                // alloc new memory: [listToFree tracker, T, ...(usableMemory tracker) T]
                const usize bytes = ALIGNMENT + ALIGNED_SIZE * numAlloc;
                Add(AllocateRaw(bytes), bytes);
                return usableMemory;
            }
        };

        // dummy allocator that does nothing
        template <class T, usize MinSize, usize MaxSize, bool IsFlat>
        struct NodeAllocator {
            // we dont use the memory
            void AddIfEnough(void* ptr, usize /*unused*/) {
                FreeRaw(ptr);
            }
        };

        template <class T, usize MinSize, usize MaxSize>
        struct NodeAllocator<T, MinSize, MaxSize, false> : BulkPoolAllocator<T, MinSize, MaxSize> {};
    }

    template <class Key, class Value>
    struct KeyValuePair {
        Key key;
        Value value;
    };

    template <class Key>
    struct KeyValuePair<Key, void> {
        Key key;
    };

    namespace HashTables {
        static constexpr usize MaxLoadFactorPer100 = 80;
        inline void AbortOverflowError() { Debug::QCritical$("hashmap encountered overflow"); }
    }

    // A highly optimized hashmap implementation, using the Robin Hood algorithm.
    //
    // This implementation uses the following memory layout:
    //
    // [Node, Node, ... Node | info, info, ... infoSentinel ]
    //
    // * Node: either a DataNode that directly has the std::pair<key, val> as member,
    //   or a DataNode with a pointer to std::pair<key,val>. Which DataNode representation to use
    //   depends on how fast the swap() operation is. Heuristically, this is automatically choosen
    //   based on sizeof(). there are always 2^n Nodes.
    //
    // * info: Each Node in the map has a corresponding info byte, so there are 2^n info bytes.
    //   Each byte is initialized to 0, meaning the corresponding Node is empty. Set to 1 means the
    //   corresponding node contains data. Set to 2 means the corresponding Node is filled, but it
    //   actually belongs to the previous position and was pushed out because that place is already
    //   taken.
    //
    // * infoSentinel: Sentinel byte set to 1, so that iterator's ++ can stop at end() without the
    //   need for a idx variable.
    //
    // According to STL, order of templates has effect on throughput. That's why I've moved the
    // boolean to the front.
    // https://www.reddit.com/r/cpp/comments/ahp6iu/compile_time_binary_size_reductions_and_cs_future/eeguck4/
    template <bool IsFlat, class Key, class Value, class Hasher>
    struct HashTable
        : Memory::NodeAllocator<KeyValuePair<Key, Value>, 4, 16384, IsFlat>,
          ICollection<KeyValuePair<Key, Value>, HashTable<IsFlat, Key, Value, Hasher>> {
        using KeyType = Key;
        using ValueType = Value;
        using PairType = KeyValuePair<Key, Value>;
        using HasherType = Hasher;
    private:
        // make sure we have 8 elements, needed to quickly rehash mInfo
        static constexpr usize InitialNumElements = sizeof(u64);
        static constexpr u32   InitialInfoBitPos = 5;
        static constexpr byte  InitialInfoInc = 1U << InitialInfoBitPos;
        static constexpr usize InfoMask = InitialInfoInc - 1U;
        static constexpr byte  InitialInfoHashShift = 0;
        using DataPool = Memory::NodeAllocator<PairType, 4, 16384, IsFlat>;

        // type needs to be wider than u8.
        using InfoType = u32;

        struct Node;

        // members are sorted so no padding occurs
        u64      hashMultiplier  = 0xc4ceb9fe1a85ec53;   // 8 byte  8
        Node*    kvData          = (Node*)BadAddress();  // 8 byte 16
        u8*      infoData        = (u8*)BadAddress();    // 8 byte 24
        usize    elmCount        = 0;                    // 8 byte 32
        usize    mask            = 0;                    // 8 byte 40
        usize    maxElmsAllowed  = 0;                    // 8 byte 48
        InfoType infoInc         = InitialInfoInc;       // 4 byte 52
        InfoType infoHashShift   = InitialInfoHashShift; // 4 byte 56
        [[no_unique_address]] Hasher hasher;

        // a dummy address that's not used but can still be read to, unlike nullptr
        const void* BadAddress()  const { return &mask; }
        // keyvals and info share the same memory, after keyval ends, info starts.
        // this is a neat shortcut to get the end of keyvals.
        const Node* KvEnd()       const { return reinterpret_cast<const Node*>(infoData); }
        // used to update info ptr
        const u8* GetNewInfoPtr() const { return kvData + elmCount; }

        // implemntation differs for large and small types:
        // for large types, we use ptrs so swapping is faster
        // for small types, we can just rely on stack memory
        struct Node {
        private:
            IfElse<IsFlat, PairType, PairType*> data;
        public:
            explicit Node(HashTable&,   Key k, Value v) requires IsFlat : data { std::move(k), std::move(v) } {}
            explicit Node(HashTable& t, Key k, Value v) requires (!IsFlat) : data(t.Allocate()) {
                new (data) PairType(std::move(k), std::move(v));
            }
            Node(HashTable&, Node&& n) : data(std::move(n.data)) {}

            // doesn't do anything since its on the stack
            void Destroy(HashTable& table) const {
                if constexpr (!IsFlat) {
                    // don't deallocate, just put it into list of datapool.
                    data->~PairType();
                    table.Deallocate(data);
                }
            }
            void DestroyNoDeallocate() const {
                if constexpr (!IsFlat)
                    data->~PairType();
            }

            const PairType* operator->() const { if constexpr (IsFlat) { return &data; } else { return data; } }
            PairType*       operator->()       { if constexpr (IsFlat) { return &data; } else { return data; } }
            const PairType& operator*()  const { return *operator->(); }
            PairType&       operator*()        { return *operator->(); }

            Key&       GetKey()       { return operator->()->key; }
            const Key& GetKey() const { return operator->()->key; }
            Value&       GetValue()       { return operator->()->value; }
            const Value& GetValue() const { return operator->()->value; }

            operator PairType&()             { return operator*(); }
            operator const PairType&() const { return operator*(); }
            operator Key&()                  { return GetKey(); }
            operator const Key&()      const { return GetKey(); }
            operator Value&()                { return GetValue(); }
            operator const Value&()    const { return GetValue(); }
        };

        static void DestroyNodesNoDeallocate(HashTable& m) {
            m.elmCount = 0;
            if constexpr (!IsFlat || !TrivialDestruct<Node>) {
                // clear also resets mInfo to 0, that's sometimes not necessary.
                const usize numElmsWithBuf = m.GetElmsWithBuffer(m.mask + 1);
                for (usize i = 0; i < numElmsWithBuf; ++i) {
                    if (m.infoData[i] != 0) {
                        Node& n = m.kvData[i];
                        n.DestroyNoDeallocate();
                        n.~Node();
                    }
                }
            }
        }

        // generic iterator for keys, values, valuesmut, pairs, and pairsmut
        template <class T>
        struct TableIter : IIterator<T&, TableIter<T>> {
            friend IIterator<AddConstIf<PairType, T>&, TableIter>;
        private:
            using NodePtr = AddConstIf<Node, T>*;
            friend struct HashTable;
            NodePtr kvData = nullptr;
            const Node* kvEnd = nullptr;
            const u8* infoData = nullptr;

            TableIter(NodePtr kv, const Node* end, const u8* inf) : kvData(kv), kvEnd(end), infoData(inf) {}
        public:
            using Item = T&;

            TableIter() = default;
            TableIter(const TableIter&) = default;
            TableIter(TableIter&&) = default;
            // Iter<T> -> Iter<const T>
            TableIter(const TableIter<RemConst<T>>& other) requires IsConst<T>
                : kvData(other.kvData), kvEnd(other.kvEnd), infoData(other.infoData) {}

            static TableIter FromFwd(NodePtr kv, const Node* end, const u8* inf) {
                TableIter it { kv, end, inf };
                it.FastForward();
                return it;
            }

            void FastForward() {
                usize n;
                while ((n = Memory::ReadU64Native(infoData)) == 0) {
                    infoData += sizeof(u64);
                    kvData += sizeof(u64);
                }

                u32 inc;
                if constexpr (Memory::IsLittleEndian()) {
                    inc = usizes::CountRightZeros(n) / 8;
                } else {
                    inc = usizes::CountLeftZeros(n) / 8;
                }

                kvData += inc;
                infoData += inc;
            }

            Item CurrentImpl() const {
                return (Item)*kvData;
            }
            void AdvanceImpl() {
                ++infoData;
                ++kvData;
                FastForward();
            }
            bool CanNextImpl() const { return kvData != kvEnd; }
        };
    public:
        // Creates an empty hash map. Nothing is allocated yet, this happens at the first insert.
        // This tremendously speeds up ctor & dtor of a map that never receives an element. The
        // penalty is payed at the first insert, and not before. Lookup of this empty map works
        // because everybody points to DummyInfoByte::b. parameter bucket_count is dictated by the
        // standard, but we can ignore it.
        explicit HashTable(Hasher h = {}) : hasher(std::move(h)) {}

        HashTable(Collection<PairType> auto&& kvpairs, Hasher h = {}) : hasher(std::move(h)) {
            Insert(kvpairs);
        }

        HashTable(IList<PairType> initlist, Hasher h = {}) : hasher(std::move(h)) {
            Insert(Spans::FromIList(initlist));
        }

        static HashTable WithCap(usize cap, Hasher h = {}) {
            HashTable ht = { std::move(h) };
            ht.Reserve(cap);
            return ht;
        }

        void MemberwiseCopy(HashTable& t) {
            hashMultiplier = t.hashMultiplier;
            kvData         = t.kvData;
            infoData       = t.infoData;
            elmCount       = t.elmCount;
            mask           = t.mask;
            maxElmsAllowed = t.maxElmsAllowed;
            infoInc        = t.infoInc;
            infoHashShift  = t.infoHashShift;
        }

        HashTable(HashTable&& t) noexcept : DataPool(std::move(t.GetDataPool())),
                                            hasher(std::move(t.hasher)) {
            if (t.mask) {
                MemberwiseCopy(t);
                // set other's mask to 0 so its destructor won't do anything
                t.Init();
            }
        }

        HashTable& operator=(HashTable&& t) noexcept {
            if (&t == this) return *this;

            if (t.mask != 0) {
                // only move stuff if the other map actually has some data
                Destroy();
                MemberwiseCopy(t);
                DataPool::operator=(std::move(t.GetDataPool()));
                t.Init();
            } else {
                // nothing in the other map => just clear us.
                Clear();
            }
            return *this;
        }

        HashTable(const HashTable& t) : hasher(t.hasher) {
            if (t.IsEmpty()) return;
            // not empty: create an exact copy. it is also possible to just iterate through all
            // elements and insert them, but copying is probably faster.

            const usize elmsWithBuf = GetElmsWithBuffer(t.mask + 1);
            const usize bytesTotal = GetTotalBytes(elmsWithBuf);

            MemberwiseCopy(t);
            hashMultiplier = t.hashMultiplier;
            kvData = (Node*)Memory::AllocateRaw(bytesTotal);
            // no need for calloc because clonData does memcpy
            infoData = reinterpret_cast<u8*>(kvData + elmsWithBuf);
            CloneTable(t, *this);
        }

        // Creates a copy of the given map. Copy constructor of each entry is used.
        HashTable& operator=(const HashTable& t) {
            if (&t == this) return *this;

            // we keep using the old allocator and not assign the new one, because we want to keep
            // the memory available. when it is the same size.
            if (t.IsEmpty()) {
                if (mask == 0) {
                    // nothing to do, we are empty too
                    return *this;
                }
                // not empty: destroy what we have there
                // clear also resets mInfo to 0, that's sometimes not necessary.
                Destroy();
                Init();

                return *this;
            }

            // clean up old stuff
            DestroyNodes(*this);

            if (mask != t.mask) {
                // no luck: we don't have the same array size allocated, so we need to realloc.
                if (mask != 0) {
                    // only deallocate if we actually have data!
                    Memory::FreeRaw(kvData);
                }

                const usize elmsWithBuf = GetElmsWithBuffer(t.mMask + 1);
                const usize numBytesTotal = GetTotalBytes(elmsWithBuf);
                kvData = (Node*)Memory::AllocateRaw(numBytesTotal);

                // no need for calloc here because cloneData performs a memcpy.
                infoData = reinterpret_cast<u8*>(kvData + elmsWithBuf);
                // sentinel is set in cloneData
            }
            hashMultiplier = t.hashMultiplier;
            elmCount       = t.elmCount;
            mask           = t.mask;
            maxElmsAllowed = t.maxElmsAllowed;
            infoInc        = t.infoInc;
            infoHashShift  = t.infoHashShift;
            hasher         = t.hasher;
            CloneTable(t, *this);

            return *this;
        }

        // Destroys the map and all it's contents.
        ~HashTable() { Destroy(); }

        // fast path: Just copy data, without allocating anything.
        static void CloneTable(const HashTable& src, HashTable& dest) {
            if constexpr (IsFlat && TrivialCopy<Node>) {
                const auto* source = reinterpret_cast<const char*>(src.kvData);
                const auto* destn  = reinterpret_cast<char*>(dest.kvData);
                Memory::RangeCopy(destn, source, dest.GetElmsWithBuffer(dest.mask + 1));
            } else {
                const usize numElmWithBuf = dest.GetElmsWithBuffer(dest.mask + 1);
                Memory::RangeCopy(dest.infoData, src.infoData, dest.CalcNumBytesInfo(numElmWithBuf));

                for (usize i = 0; i < numElmWithBuf; ++i) {
                    if (dest.infoData[i])
                        new (&dest.kvData[i]) Node(dest, *src.kvData[i]);
                }
            }
        }

        static void DestroyNodes(HashTable& table) {
            table.elmCount = 0;
            if constexpr (!IsFlat || !TrivialDestruct<Node>) {
                // clear also resets mInfo to 0, that's sometimes not necessary.
                const usize numElmWithBuf = table.GetElmsWithBuffer(table.mask + 1);

                for (usize i = 0; i < numElmWithBuf; ++i) {
                    if (table.infoData[i] != 0) {
                        Node& n = table.kvData[i];
                        n.Destroy(table);
                        n.~Node();
                    }
                }
            }
        }

        // Clears all data, without resizing.
        void Clear() {
            if (IsEmpty()) {
                // don't do anything! also important because we don't want to write to
                // DummyInfoByte::b, even though we would just write 0 to it.
                return;
            }

            DestroyNodes(*this);
            const usize numElmsWithBuf = GetElmsWithBuffer(mask + 1);
            // clear everything, then set the sentinel again
            Memory::MemSet(infoData, 0, CalcNumBytesInfo(numElmsWithBuf));
            infoData[numElmsWithBuf] = 1;

            infoInc = InitialInfoInc;
            infoHashShift = InitialInfoHashShift;
        }

        const DataPool& GetDataPool() const { return static_cast<const DataPool&>(*this); }
        DataPool&       GetDataPool()       { return static_cast<DataPool&>      (*this); }
        const Hasher&   GetHasher()   const { return hasher; }
        Hasher&         GetHasher()         { return hasher; }

        usize Count()   const { return elmCount; }
        static usize MaxCount() { return u64s::MAX; }
        bool IsEmpty()  const { return elmCount == 0; }
        explicit operator bool() const { return elmCount != 0; }

        static float MaxLoadFactor() { return HashTable::MaxLoadFactorPer100 / 100.0F; }
        // Average number of elements per bucket. Since we allow only 1 per bucket
        float LoadFactor() const { return (float)Count() / (mask + 1); }
        usize GetMask() const { return mask; }

        // Checks if both tables contain the same entries. Order is irrelevant.
        bool operator==(const HashTable& other) const {
            if (Count() != other.Count()) return false;

            for (const auto& otherEntry : other) {
                if (!Contains(otherEntry))
                    return false;
            }

            return true;
        }

        Value& operator[](const Key& key) {
            const auto [index, result] = InsertKeyAndPrepareSlot(key);
            switch (result) {
                case InsertResult::New: case InsertResult::Overwrite:
                    InitOrWriteNode(index, key, Value {}, result);
                default:;
            }
            return kvData[index].GetValue();
        }
        Value& operator[](Key&& key) {
            const auto [index, result] = InsertKeyAndPrepareSlot(key);
            switch (result) {
                case InsertResult::New: case InsertResult::Overwrite:
                    InitOrWriteNode(index, std::move(key), Value {}, result);
                default:;
            }
            return kvData[index].GetValue();
        }
        OptRef<const Value> operator[](const Key& key) const { return Get(key); }
        OptRef<const Value> Get(const Key& key) const {
            const OptionUsize i = FindIndexOf(key);
            return i ? OptRefs::SomeRef(kvData[*i].GetValue()) : nullptr;
        }
        OptRef<const Value> operator[](const auto& kview) const { return Get(kview); }
        OptRef<const Value> Get(const auto& kview) const {
            const OptionUsize i = FindIndexOf(kview);
            return i ? OptRefs::SomeRef(kvData[*i].GetValue()) : nullptr;
        }

    private:
        // highly performance relevant code.
        // Lower bits are used for indexing into the array (2^n size)
        // The upper 1-5 bits need to be a reasonable good hash, to save comparisons.
        void HashKeyToIndex(const auto& key, usize* idx, InfoType* info) const {
            // In addition to whatever hash is used, add another mul & shift so we get better hashing.
            // This serves as a bad hash prevention, if the given data is
            // badly mixed.
            u64 h = (u64)hasher(key);
            h *= hashMultiplier;
            h ^= h >> 33;

            // the lower InitialInfoNumBits are reserved for info.
            *info = infoInc + (InfoType)((h & InfoMask) >> infoHashShift);
            *idx = ((usize)h >> InitialInfoBitPos) & mask;
        }

        // forwards the index by one, wrapping around at the end
        void Next(InfoType* info, usize* idx) const {
            ++*idx;
            *info += infoInc;
        }

        void NextWhileLessThan(InfoType* info, usize* idx) const {
            while (*info < infoData[*idx]) {
                Next(info, idx);
            }
        }

        // shift everything up by one element. Tries to move stuff around.
        void ShiftUp(usize startIdx, usize insertIdx) {
            new (&kvData[startIdx]) Node(*this, std::move(kvData[startIdx - 1]));
            for (usize i = startIdx; --i != insertIdx; ) {
                kvData[i] = std::move(kvData[i - 1]);
            }

            for (usize i = startIdx; i != insertIdx; --i) {
                infoData[i] = (u8)(infoData[i - 1] + infoInc);
                if (infoData[i] + infoInc > 0xFF) [[unlikely]]
                    maxElmsAllowed = 0;
            }
        }

        void ShiftDown(usize idx) {
            kvData[idx].Destroy(*this);

            // until we find one that is either empty or has zero offset.
            while (infoData[idx + 1] >= 2 * infoInc) {
                infoData[idx] = (u8)(infoData[idx + 1] - infoInc);
                kvData[idx] = std::move(kvData[idx + 1]);
                ++idx;
            }

            infoData[idx] = 0;
            // don't destroy, we've moved it
            // mKeyVals[idx].Destroy(*this);
            kvData[idx].~Node();
        }

        OptionUsize FindIndexOf(const auto& key) const {
            usize index = 0;
            InfoType inf = 0;
            HashKeyToIndex(key, &index, &inf);

            do {
                // unrolling this twice gives a bit of a speedup. More unrolling did not help.
                if (inf == infoData[index] && key == kvData[index].GetKey())
                    return index;

                Next(&inf, &index);

                if (inf == infoData[index] && key == kvData[index].GetKey())
                    return index;

                Next(&inf, &index);
            } while (inf <= infoData[index]);

            // nothing found!
            return nullptr;
        }

        // inserts a keyval that is guaranteed to be new, e.g. when the hashmap is resized.
        void InsertGuarenteedNew(Node&& node) {
            // we don't retry, fail if overflowing
            // don't need to check max num elements
            if (0 == maxElmsAllowed && !TryIncreaseInfo()) {
                HashTables::AbortOverflowError();
            }

            usize index = 0;
            InfoType inf = 0;
            HashKeyToIndex(node.GetKey(), &index, &inf);

            // skip forward. Use <= because we are certain that the element is not there.
            while (inf <= infoData[index]) {
                index = index + 1;
                inf += infoInc;
            }

            // key not found, so we are now exactly where we want to insert it.
            const usize insertIndex = index;
            const u8    insertInfo  = (u8)inf;
            if (insertInfo + infoInc > 0xFF) [[unlikely]]
                maxElmsAllowed = 0;

            // find an empty spot
            while (infoData[index] != 0) {
                Next(&inf, &index);
            }

            auto& l = kvData[insertIndex];
            if (index == insertIndex) {
                new (&l) Node(*this, std::move(node));
            } else {
                ShiftUp(index, insertIndex);
                l = std::move(node);
            }

            // put at empty spot
            infoData[insertIndex] = insertInfo;
            ++elmCount;
        }
    public:
        void Insert(const Collection<PairType> auto& collection) {
            for (auto&& kv : collection)
                Insert(kv);
        }

        void Insert(IList<PairType> ilist) {
            for (const auto& kv : ilist)
                Insert(kv);
        }

        enum class InsertResult { Found, New, Overwrite, OverflowError };

        void InitOrWriteNode(usize index, Key k, Value v, InsertResult r) {
            switch (r) {
                case InsertResult::New:
                    new (&kvData[index]) Node(*this, std::move(k), std::move(v));
                    break;
                case InsertResult::Overwrite:
                    kvData[index] = Node(*this, std::move(k), std::move(v));
                    break;
                default:;
            }
        }

        // Finds key, and if not already present prepares a spot where to put the key & value.
        // This potentially shifts nodes out of the way, updates info and number of inserted
        // elements, so the only operation left to do is create/assign a new node at that spot.
        Tuple<usize, InsertResult> InsertKeyAndPrepareSlot(const Key& key) {
            for (int tries = 0; tries < 256; ++tries) {
                usize i = 0;
                InfoType inf = 0;
                HashKeyToIndex(key, &i, &inf);
                NextWhileLessThan(&inf, &i);

                // while we potentially have a match
                while (inf == infoData[i]) {
                    if (key == kvData[i].GetKey())
                        // key already exists, do NOT insert.
                        // see http://en.cppreference.com/w/cpp/container/unordered_map/insert
                        return { i, InsertResult::Found };
                    Next(&inf, &i);
                }

                // unlikely that this evaluates to true
                if (elmCount >= maxElmsAllowed) [[unlikely]] {
                    IncreaseSize();
                    continue;
                }

                // key not found, so we are now exactly where we want to insert it.
                const usize    insertIndex = i;
                const InfoType insertInfo  = inf;
                if (insertInfo + infoInc > 0xFF)
                    maxElmsAllowed = 0;

                // find an empty spot
                while (infoData[i] != 0)
                    Next(&inf, &i);

                if (i != insertIndex)
                    ShiftUp(i, insertIndex);
                // put at empty spot
                infoData[insertIndex] = static_cast<u8>(insertInfo);
                ++elmCount;
                return { insertIndex, i == insertIndex ? InsertResult::New : InsertResult::Overwrite };
            }

            // enough attempts failed, so finally give up.
            HashTables::AbortOverflowError();
            return { 0, InsertResult::OverflowError };
        }

    private:
        // tries to insert a new value and returns a reference, unless one already exists
        template <class Kfwd>
        OptRef<PairType> TryInsertInternal(Kfwd&& k, Value v) {
            const auto [i, result] = InsertKeyAndPrepareSlot(k);
            InitOrWriteNode(i, std::forward<Kfwd>(k), std::move(v), result);
            return result == InsertResult::Found ? nullptr : *kvData[i];
        }

        // sets the value even if it was found,
        // and returns true if the value is new or false if it was overwritten
        template <class Kfwd>
        Tuple<PairType&, bool> InsertOrAssignInternal(Kfwd&& k, Value v) {
            const auto [i, result] = InsertKeyAndPrepareSlot(k);
            switch (result) {
                case InsertResult::Found:
                    kvData[i].GetValue() = std::move(v);
                break;
                case InsertResult::New:
                    new (&kvData[i]) Node(*this, std::forward<Kfwd>(k), std::move(v));
                break;
                case InsertResult::Overwrite:
                    kvData[i] = Node(*this, std::forward<Kfwd>(k), std::move(v));
                default:;
            }
            return { kvData[i], result != InsertResult::Found };
        }

        // returns the previous value associated with the key, unless there wasn't any to begin with
        // also writes the new value to the associated key
        template <class Kfwd>
        Option<Value> ReplaceInternal(Kfwd&& k, Value v) {
            const auto [i, result] = InsertKeyAndPrepareSlot(k);
            switch (result) {
                case InsertResult::Found:
                    std::swap(kvData[i].GetValue(), v);
                    return v;
                case InsertResult::New:
                    new (&kvData[i]) Node(*this, std::forward<Kfwd>(k), std::move(v));
                break;
                case InsertResult::Overwrite:
                    kvData[i] = Node(*this, std::forward<Kfwd>(k), std::move(v));
                default:;
            }
            return nullptr;
        }
    public:
        OptRef<PairType> TryInsert(const Key& k, Value v) { return TryInsertInternal(k,            std::move(v)); }
        OptRef<PairType> TryInsert(Key&& k,      Value v) { return TryInsertInternal(std::move(k), std::move(v)); }
        Tuple<PairType&, bool> InsertOrAssign(const Key& k, Value v) { return InsertOrAssignInternal(k,            std::move(v)); }
        Tuple<PairType&, bool> InsertOrAssign(Key&&      k, Value v) { return InsertOrAssignInternal(std::move(k), std::move(v)); }
        PairType& Insert(const Key& k, Value v) { return InsertOrAssignInternal(k,            std::move(v))[1_st]; }
        PairType& Insert(Key&&      k, Value v) { return InsertOrAssignInternal(std::move(k), std::move(v))[1_st]; }
        Option<Value> Replace(const Key& k, Value v) { return ReplaceInternal(k,            std::move(v)); }
        Option<Value> Replace(Key&&      k, Value v) { return ReplaceInternal(std::move(k), std::move(v)); }

        // removes the key in the map
        bool Remove(const Key& k) {
            const OptionUsize i = FindIndexOf(k);
            if (!i) return false;

            ShiftDown(i);
            --elmCount;
            return true;
        }

        void RemoveAt(TableIter<const PairType>& iter) {
            const usize i = iter.kvData - kvData;
            ShiftDown(i);
            --elmCount;

            if (!*iter.infoData) {
                iter.Advance();
            }
        }

        void KeepEntries(Predicate<PairType> auto&& pred) {
            for (auto iter = IterImpl(); iter.CanNext(); iter.Advance()) {
                if (!pred(iter.Current()))
                    RemoveAt(iter);
            }
        }

        // removes the key value pair, and returns the value as well
        Option<Value> Take(const Key& k) {
            const OptionUsize i = FindIndexOf(k);
            if (!i) return nullptr;

            Value val = std::move(kvData[*i].GetValue());
            ShiftDown(i);
            --elmCount;
            return val;
        }

        // removes the key value pair, and returns the pair as well
        Option<PairType> TakeEntry(const Key& k) {
            const OptionUsize i = FindIndexOf(k);
            if (!i) return nullptr;

            PairType kvpair = std::move(*kvData[*i]);
            ShiftDown(i);
            --elmCount;
            return kvpair;
        }

        bool Contains(const Key& key) const {
            return FindIndexOf(key).HasValue();
        }
        bool Contains(const auto& kview) const {
            return FindIndexOf(kview).HasValue();
        }
    protected:
        TableIter<const PairType> IterImpl() const { return TableIter<const PairType>::FromFwd(kvData, KvEnd(), infoData); }
        TableIter<PairType>    IterMutImpl()       { return TableIter<PairType>      ::FromFwd(kvData, KvEnd(), infoData); }
    public:
        TableIter<const PairType> IterStartingAt(const Key& k) const {
            const OptionUsize i = FindIndexOf(k);
            if (!i) return {};
            return { &kvData[*i], KvEnd(), &infoData[*i] };
        }

        TableIter<const Key>   Keys()   const { return TableIter<const Key>  ::FromFwd(kvData, KvEnd(), infoData); }
        TableIter<const Value> Values() const { return TableIter<const Value>::FromFwd(kvData, KvEnd(), infoData); }
        TableIter<Value>       ValuesMut()    { return TableIter<Value>      ::FromFwd(kvData, KvEnd(), infoData); }

        // reserves space for the specified number of elements. Makes sure the old data fits.
        // exactly the same as reserve(c).
        void Rehash(usize c) {
            // forces a reserve
            ReserveFor(c, true);
        }

        // reserves space for the specified number of elements. Makes sure the old data fits.
        // Exactly the same as rehash(c). Use rehash(0) to shrink to fit.
        void Reserve(usize c) {
            // reserve, but don't force rehash
            ReserveFor(c, false);
        }

        // If possible reallocates the map to a smaller one. This frees the underlying table.
        // Does not do anything if load_factor is too large for decreasing the table's size.
        void Compact() {
            usize newSize = InitialNumElements;
            while (GetMaxElmsAllowed(newSize) < elmCount && newSize != 0)
                newSize *= 2;

            if (newSize == 0) [[unlikely]]
                HashTables::AbortOverflowError();

            // only actually do anything when the new size is bigger than the old one. This prevents to
            // continuously allocate for each reserve() call.
            if (newSize < mask + 1) {
                RehashPowOf2(newSize, true);
            }
        }

        usize GetMaxElmsAllowed(usize maxElements) const {
            if (maxElements <= usizes::MAX / 100) [[likely]] {
                return maxElements * HashTables::MaxLoadFactorPer100 / 100;
            }
            // we might be a bit inprecise, but since maxElements is quite large that doesn't matter
            return (maxElements / 100) * HashTables::MaxLoadFactorPer100;
        }

        usize CalcNumBytesInfo(usize numElements) const {
            // we add a u64, which houses the sentinel (first byte) and padding so we can load
            // 64 bit types.
            return numElements + sizeof(u64);
        }

        usize GetElmsWithBuffer(usize numElements) const {
            const usize maxElmsAllowedFor = GetMaxElmsAllowed(numElements);
            return numElements + std::min<usize>(maxElmsAllowedFor, 0xFF);
        }

        // calculation only allowed for 2^n values
        usize GetTotalBytes(usize numElements) const {
            return numElements * sizeof(Node) + CalcNumBytesInfo(numElements);
        }
    private:
        void ReserveFor(usize c, bool forceRehash) {
            const usize minElementsAllowed = std::max(c, elmCount);
            usize newSize = InitialNumElements;
            while (GetMaxElmsAllowed(newSize) < minElementsAllowed && newSize != 0) {
                newSize *= 2;
            }
            if (newSize == 0) [[unlikely]] {
                HashTables::AbortOverflowError();
            }

            // only actually do anything when the new size is bigger than the old one. This prevents to
            // continuously allocate for each reserve() call.
            if (forceRehash || newSize > mask + 1) {
                RehashPowOf2(newSize, false);
            }
        }

        // reserves space for at least the specified number of elements.
        // only works if numBuckets if power of two
        // True on success, false otherwise
        void RehashPowOf2(usize numBuckets, bool forceFree) {
            Node* oldKeyVals = kvData;
            const u8* oldInfo = infoData;

            const usize oldMaxElms = GetElmsWithBuffer(mask + 1);

            // resize operation: move stuff
            InitData(numBuckets);
            if (oldMaxElms <= 1) return;

            for (usize i = 0; i < oldMaxElms; ++i) {
                if (oldInfo[i] != 0) {
                    // might throw an exception, which is really bad since we are in the middle of
                    // moving stuff.
                    InsertGuarenteedNew(std::move(oldKeyVals[i]));
                    // destroy the node but DON'T destroy the data.
                    oldKeyVals[i].~Node();
                }
            }

            // this check is not necessary as it's guarded by the previous if, but it helps
            // silence g++'s overeager "attempt to free a non-heap object 'map'
            // [-Werror=free-nonheap-object]" warning.
            if (oldKeyVals != BadAddress()) {
                // don't destroy old data: put it into the pool instead
                if (forceFree) {
                    Memory::FreeRaw(oldKeyVals);
                } else {
                    DataPool::AddIfEnough(oldKeyVals, GetTotalBytes(oldMaxElms));
                }
            }
        }

        void InitData(usize maxElms) {
            elmCount = 0;
            mask = maxElms - 1;
            maxElmsAllowed = GetMaxElmsAllowed(maxElms);

            const usize numElmWithBuf = GetElmsWithBuffer(maxElms);
            // malloc & zero mInfo. Faster than calloc everything.
            const usize numBytesTotal = GetTotalBytes(numElmWithBuf);

            kvData = (Node*)Memory::AllocateRaw(numBytesTotal);
            infoData    = reinterpret_cast<u8*>(kvData + numElmWithBuf);
            Memory::MemSet(infoData, 0, numBytesTotal - numElmWithBuf * sizeof(Node));
            // set sentinel
            infoData[numElmWithBuf] = 1;

            infoInc       = InitialInfoInc;
            infoHashShift = InitialInfoHashShift;
        }

        bool TryIncreaseInfo() {
            if (infoInc <= 2) {
                // need to be > 2 so that shift works (otherwise undefined behavior!)
                return false;
            }
            // we got space left, try to make info smaller
            infoInc >>= 1;

            // remove one bit of the hash, leaving more space for the distance info.
            // This is extremely fast because we can operate on 8 bytes at once.
            ++infoHashShift;
            const usize numElmsWithBuf = GetElmsWithBuffer(mask + 1);

            for (usize i = 0; i < numElmsWithBuf; i += 8) {
                u64 x = Memory::ReadU64Native(infoData + i);
                x = (x >> 1U) & 0x7f7f7f7f7f7f7f7f;
                Memory::WriteU64Native(x, infoData + i);
            }
            // update sentinel, which might have been cleared out!
            infoData[numElmsWithBuf] = 1;

            maxElmsAllowed = GetMaxElmsAllowed(mask + 1);
            return true;
        }

        void IncreaseSize() {
            // nothing allocated yet? just allocate InitialNumElements
            if (mask == 0) {
                InitData(InitialNumElements);
                return;
            }

            const usize maxElmsAllowedFor = GetMaxElmsAllowed(mask + 1);
            if (elmCount < maxElmsAllowedFor && TryIncreaseInfo())
                return;

            if (elmCount * 2 < GetMaxElmsAllowed(mask + 1)) {
                // we have to resize, even though there would still be plenty of space left!
                // Try to rehash instead. Delete freed memory so we don't steadyily increase mem in case
                // we have to rehash a few times
                UpdateNextHashMultiplier();
                RehashPowOf2(mask + 1, true);
            } else {
                // we've reached the capacity of the map, so the hash seems to work nice. Keep using it.
                RehashPowOf2((mask + 1) * 2, false);
            }
        }

        void UpdateNextHashMultiplier() {
            // adding an *even* number, so that the multiplier will always stay odd. This is necessary
            // so that the hash stays a mixing function (and thus doesn't have any information loss).
            hashMultiplier += 0xc4ceb9fe1a85ec54;
        }

        void Destroy() {
            if (mask == 0) {
                // don't deallocate!
                return;
            }

            DestroyNodesNoDeallocate(*this);
            // This protection against not deleting mMask shouldn't be needed as it's sufficiently
            // protected with the 0==mMask check, but I have this anyways because g++ 7 otherwise
            // reports a compile error: attempt to free a non-heap object 'fm'
            // [-Werror=free-nonheap-object]
            if (kvData != BadAddress()) {
                Memory::FreeRaw(kvData);
            }
        }

        void Init() {
            kvData         = (Node*)BadAddress();
            infoData       = (u8*)BadAddress();
            elmCount       = 0;
            mask           = 0;
            maxElmsAllowed = 0;
            infoInc        = InitialInfoInc;
            infoHashShift  = InitialInfoHashShift;
        }

        friend ICollection<KeyValuePair<Key, Value>, HashTable>;
    };

    template <class K, class V, class Hasher = Hashing::DefaultHasher>
    struct HashMap : HashTable<sizeof(KeyValuePair<K, V>) <= sizeof(usize) * 6, K, V, Hasher> {};

    template <class K, class Hasher = Hashing::DefaultHasher>
    struct HashSet : HashTable<sizeof(K) <= sizeof(usize) * 6, K, void, Hasher> {};
}