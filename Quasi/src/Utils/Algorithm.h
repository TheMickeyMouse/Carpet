#pragma once
#include "Vec.h"

namespace Quasi::Algorithm {
    constexpr usize MAX_STACK_ARRAY_SIZE = 4096;

    template <class T>
    Tuple<bool, usize> BinarySearchWith(Span<T> span, Fn<Comparison, const T&> auto&& cmp) {
        usize len = span.Length();
        if (len == 0) return { false, 0 };
        usize i = 0;
        while (len > 1) {
            const usize half = len / 2, mid = i + half;
            i = (cmp(span[mid]) > 0) ? i : mid;
            len -= half;
        }
        const Comparison compRes = cmp(span[i]);
        if (compRes == Cmp::EQUAL) {
            return { true, i };
        } else {
            return { false, i + (compRes < 0) };
        }
    }

    template <class T>
    usize BinaryPartitionPoint(Span<T> span, Predicate<T> auto&& left) {
        const auto [found, idx] = BinarySearchWith(span, [&] (const T& x) { return left(x) ? Cmp::LESS : Cmp::GREATER; });
        return idx;
    }

    // the lower bound is the same as BinarySearch
    template <class T>
    usize UpperBound(Span<T> span, Comparator<T> auto&& cmp) {
        usize len = span.Length();
        if (len == 0) return 0;
        usize i = 0;
        while (len > 1) {
            const usize half = len, mid = i + half;
            i = (cmp(span[mid]) >= 0) ? mid : i;
            len -= half;
        }
        return i + (cmp(span[i]) <= 0);
    }

    // sorting algorithm ipnsort from https://github.com/Voultapher/sort-research-rs/blob/main/ipnsort/src/lib.rs
    namespace SortingDetails {
        namespace SmallSort {
            /// Optimal number of comparisons, and good perf.
            constexpr usize SMALL_SORT_FALLBACK_THRESHOLD = 16;

            /// SAFETY: If you change this value, you have to adjust [`small_sort_general`] !
            constexpr usize SMALL_SORT_GENERAL_THRESHOLD = 32;

            /// [`small_sort_general`] uses [`sort8_stable`] as primitive and does a kind of ping-pong merge,
            /// where the output of the first two [`sort8_stable`] calls is stored at the end of the scratch
            /// buffer. This simplifies panic handling and avoids additional copies. This affects the required
            /// scratch buffer size.
            ///
            /// SAFETY: If you change this value, you have to adjust [`small_sort_general`] !
            constexpr usize SMALL_SORT_GENERAL_SCRATCH_LEN = SMALL_SORT_GENERAL_THRESHOLD + 16;

            /// SAFETY: If you change this value, you have to adjust [`small_sort_network`] !
            constexpr usize SMALL_SORT_NETWORK_THRESHOLD = 32;
            constexpr usize SMALL_SORT_NETWORK_SCRATCH_LEN = SMALL_SORT_NETWORK_THRESHOLD;

            enum class SortingStrat { FALLBACK, GENERAL, NETWORK };
            template <class T>
            constexpr SortingStrat CategorizeSortType() {
                if (TrivialCopy<T> && sizeof(T) <= sizeof(u64)
                                   && sizeof(T) * SMALL_SORT_NETWORK_SCRATCH_LEN <= MAX_STACK_ARRAY_SIZE) {
                    return SortingStrat::NETWORK;
                                   }
                if (sizeof(T) * SMALL_SORT_GENERAL_SCRATCH_LEN <= MAX_STACK_ARRAY_SIZE) {
                    return SortingStrat::GENERAL;
                }
                return SortingStrat::FALLBACK;
            }

            constexpr usize IntoSortThreshold(SortingStrat strat) {
                switch (strat) {
                    case SortingStrat::FALLBACK: return SMALL_SORT_FALLBACK_THRESHOLD;
                    case SortingStrat::GENERAL:  return SMALL_SORT_GENERAL_THRESHOLD;
                    case SortingStrat::NETWORK:  return SMALL_SORT_NETWORK_THRESHOLD;
                    default:                     return 0;
                }
            }

            template <class T> void SmallSortFallback(Span<T> span, Comparator<T> auto&& cmp, usize sortedOffset = 1);
            template <class T> void SmallSortGeneral (Span<T> span, Comparator<T> auto&& cmp);
            template <class T> void SmallSortNetwork (Span<T> span, Comparator<T> auto&& cmp);

            template <class T>
            void SmallSort(Span<T> span, Comparator<T> auto&& cmp) {
                switch (CategorizeSortType<T>()) {
                    case SortingStrat::FALLBACK: return SmallSortFallback(span, cmp);
                    case SortingStrat::GENERAL:  return SmallSortGeneral(span, cmp);
                    case SortingStrat::NETWORK:  return SmallSortNetwork(span, cmp);
                    default:                     return;
                }
            }

            template <class T> void SmallSortInsertTail(T* begin, T* tail, Comparator<T> auto&& cmp);
            template <class T> void SmallSortGeneralScratched(Span<T> span, Span<T> scratch, Comparator<T> auto&& cmp);
            template <class T> void SortStable4(T* begin, T* dest, Comparator<T> auto&& cmp);
            template <class T> void SortStable8(T* begin, T* dest, T* scratchBegin, Comparator<T> auto&& cmp);
            template <class T> void SmallSortBidirMerge(Span<T> span, T* dest, Comparator<T> auto&& cmp);
            template <class T> void SmallSortMergeUp  (T*& leftSrc, T*& rightSrc, usize rem[2], T*& dest, Comparator<T> auto&& cmp);
            template <class T> void SmallSortMergeDown(T*& leftSrc, T*& rightSrc, usize rem[2], T*& dest, Comparator<T> auto&& cmp);
            template <class T> void SwapIfLess(T* leftBeg, T* rightBeg, Comparator<T> auto&& cmp);
            template <class T> void SmallSortOptimal9(T* begin, Comparator<T> auto&& cmp);
            template <class T> void SmallSortOptimal13(T* begin, Comparator<T> auto&& cmp);

            // insertion sort
            template <class T>
            void SmallSortFallback(Span<T> span, Comparator<T> auto&& cmp, usize sortedOffset) {
                if (span.Length() < 2) return;

                // SAFETY: see individual comments.
                // We write this basic loop directly using pointers, as when we use a
                // for loop LLVM likes to unroll this loop which we do not want.
                // SAFETY: v_end is the one-past-end pointer, and we checked that
                // offset <= len, thus tail is also in-bounds.
                T* begin = span.Data(), *end = begin + span.Length();
                T* tail  = begin + sortedOffset;
                while (tail != end) {
                    // SAFETY: v_base and tail are both valid pointers to elements, and
                    // v_base < tail since we checked offset != 0.
                    SmallSortInsertTail(begin, tail, cmp);

                    // SAFETY: we checked that tail is not yet the one-past-end pointer.
                    ++tail;
                }
            }

            template <class T>
            void SmallSortInsertTail(T* begin, T* tail, Comparator<T> auto&& cmp) {
                T* before = tail - 1;
                if (cmp(*tail, *before) >= 0) return;

                // pre-destroys tail
                T tmp = std::move(*tail);
                T* dest = tail;
                // repeatidly decreases dest & before until it reaches begin
                while (true) {
                    Memory::ConstructMoveAt(dest, std::move(*before));
                    dest = before;

                    if (before == begin) break;

                    --before;
                    if (cmp(tmp, *before) >= 0) {
                        break;
                    }
                }
                // moves tail back in
                *dest = std::move(tmp);
            }

            template <class T>
            void SmallSortGeneral(Span<T> span, Comparator<T> auto&& cmp) {
                T* stackArray = (T*)_alloca(sizeof(T) * SMALL_SORT_GENERAL_SCRATCH_LEN);
                return SmallSortGeneralScratched(span, Spans::Slice(stackArray, SMALL_SORT_GENERAL_SCRATCH_LEN), cmp);
            }

            template <class T>
            void SmallSortGeneralScratched(Span<T> span, Span<T> scratch, Comparator<T> auto&& cmp) {
                const usize len = span.Length(), halfLen = len / 2;
                if (len < 2) return;

                T* begin = span.Data(), *scratchBegin = scratch.Data();

                usize sortedLen;
                if (sizeof(T) <= 16 && len >= 16) {
                    SortStable8(begin,           scratchBegin,           scratchBegin + len,     cmp);
                    SortStable8(begin + halfLen, scratchBegin + halfLen, scratchBegin + len + 8, cmp);
                    sortedLen = 8;
                } else if (len >= 8) {
                    SortStable4(begin,           scratchBegin,           cmp);
                    SortStable4(begin + halfLen, scratchBegin + halfLen, cmp);
                    sortedLen = 4;
                } else {
                    Memory::ConstructMoveAt(&scratchBegin[0],       std::move(begin[0]));
                    Memory::ConstructMoveAt(&scratchBegin[halfLen], std::move(begin[halfLen]));
                    sortedLen = 1;
                }

                {
                    T* src = begin, *dst = scratchBegin;
                    for (usize i = sortedLen; i < halfLen; ++i) {
                        Memory::ConstructMoveAt(&dst[i], std::move(src[i]));
                        SmallSortInsertTail(dst, dst + i, cmp);
                    }
                }
                {
                    T* src = begin + halfLen, *dst = scratchBegin + halfLen;
                    for (usize i = sortedLen; i < len - halfLen; ++i) {
                        Memory::ConstructMoveAt(&dst[i], std::move(src[i]));
                        SmallSortInsertTail(dst, dst + i, cmp);
                    }
                }

                SmallSortBidirMerge(Spans::Slice(scratchBegin, len), begin, cmp);
            }

            template <class T>
            void SortStable4(T* begin, T* dest, Comparator<T> auto&& cmp) {
                // By limiting select to picking pointers, we are guaranteed good cmov code-gen
                // regardless of type T's size. Further this only does 5 instead of 6
                // comparisons compared to a stable transposition 4 element sorting-network,
                // and always copies each element exactly once.

                // SAFETY: all pointers have offset at most 3 from v_base and dst, and are
                // thus in-bounds by the precondition.
                // Stably create two pairs a <= b and c <= d.
                const bool c1 = cmp(begin[1], begin[0]) == Cmp::LESS, c2 = cmp(begin[3], begin[2]) == Cmp::LESS;
                T& a = begin[c1], &b = begin[!c1], &c = begin[2 + c2], &d = begin[2 + !c2];

                // Compare (a, c) and (b, d) to identify max/min. We're left with two
                // unknown elements, but because we are a stable sort we must know which
                // one is leftmost and which one is rightmost.
                // c3, c4 | min max unknown_left unknown_right
                //  0,  0 |  a   d    b         c
                //  0,  1 |  a   b    c         d
                //  1,  0 |  c   d    a         b
                //  1,  1 |  c   b    a         d
                const bool c3 = cmp(c, a) == Cmp::LESS, c4 = cmp(d, b) == Cmp::LESS;
                T& min = c3 ? c : a, &max = c4 ? b : d,
                 & unknownLeft  = c3 ? a : c4 ? c : b,
                 & unknownRight = c4 ? d : c3 ? b : c;

                // Sort the last two unknown elements.
                const bool c5 = cmp(unknownRight, unknownLeft) == Cmp::LESS;
                T& lo = c5 ? unknownRight : unknownLeft, &hi = c5 ? unknownLeft : unknownRight;

                Memory::ConstructMoveAt(dest + 0, std::move(min));
                Memory::ConstructMoveAt(dest + 1, std::move(lo));
                Memory::ConstructMoveAt(dest + 2, std::move(hi));
                Memory::ConstructMoveAt(dest + 3, std::move(max));
            }

            /// SAFETY: The caller MUST guarantee that `v_base` is valid for 8 reads and
            /// writes, `scratch_base` and `dst` MUST be valid for 8 writes. The result will
            /// be stored in `dst[0..8]`.
            template <class T>
            void SortStable8(T* begin, T* dest, T* scratchBegin, Comparator<T> auto&& cmp) {
                // SAFETY: these pointers are all in-bounds by the precondition of our function.
                SortStable4(begin,     scratchBegin,     cmp);
                SortStable4(begin + 4, scratchBegin + 4, cmp);

                // SAFETY: scratch_base[0..8] is now initialized, allowing us to merge back
                // into dst.
                SmallSortBidirMerge(Spans::Slice(scratchBegin, 8), dest, cmp);
            }


            template <class T>
            void SmallSortBidirMerge(Span<T> span, T* dest, Comparator<T> auto&& cmp) {
                // It helps to visualize the merge:
                //
                // Initial:
                //
                //  |dst (in dst)
                //  |left               |right
                //  v                   v
                // [xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx]
                //                     ^                   ^
                //                     |left_rev           |right_rev
                //                                         |dst_rev (in dst)
                //
                // After:
                //
                //                      |dst (in dst)
                //        |left         |           |right
                //        v             v           v
                // [xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx]
                //       ^             ^           ^
                //       |left_rev     |           |right_rev
                //                     |dst_rev (in dst)
                //
                // In each iteration one of left or right moves up one position, and one of
                // left_rev or right_rev moves down one position, whereas dst always moves
                // up one position and dst_rev always moves down one position. Assuming
                // the input was sorted and the comparison function is correctly implemented
                // at the end we will have left == left_rev + 1, and right == right_rev + 1,
                // fully consuming the input having written it to dst.

                const usize len = span.Length(), halfLen = len / 2;
                T* src = span.Data();

                // [[assume(halfLen != 0)]];

                // SAFETY: no matter what the result of the user-provided comparison function
                // is, all 4 read pointers will always be in-bounds. Writing `dst` and `dst_rev`
                // will always be in bounds if the caller guarantees that `dst` is valid for
                // `v.len()` writes.
                T* left    = src,               * right    = src + halfLen,
                 * leftRev = src + halfLen - 1, * rightRev = src + len - 1,
                 * destRev = dest + len - 1;
                //               left,    right
                usize rem[2] = { halfLen, len - halfLen };

                while (rem[0] && rem[1]) {
                    SmallSortMergeUp(left, right, rem, dest, cmp);
                    if (rem[0] && rem[1]) {
                        SmallSortMergeDown(leftRev, rightRev, rem, destRev, cmp);
                    } else break;
                }
                Memory::RangeConstructMoveNoOverlap(dest, rem[0] ? left : right, rem[0] | rem[1]);
            }

            template <class T>
            void SmallSortMergeUp(T*& leftSrc, T*& rightSrc, usize rem[2], T*& dest, Comparator<T> auto&& cmp) {
                // This is a branchless merge utility function.
                // The equivalent code with a branch would be:
                //
                // if !is_less(&*right_src, &*left_src) {
                //     ptr::copy_nonoverlapping(left_src, dst, 1);
                //     left_src = left_src.add(1);
                // } else {
                //     ptr::copy_nonoverlapping(right_src, dst, 1);
                //     right_src = right_src.add(1);
                // }
                // dst = dst.add(1);

                // SAFETY: The caller must guarantee that `left_src`, `right_src` are valid
                // to read and `dst` is valid to write, while not aliasing.
                const bool isLeft = cmp(*rightSrc, *leftSrc) >= 0;
                T* src = isLeft ? leftSrc : rightSrc;
                Memory::ConstructMoveAt(dest, std::move(*src));
                rightSrc += !isLeft;
                leftSrc  +=  isLeft;
                --rem[!isLeft];
                ++dest;
            }

            template <class T>
            void SmallSortMergeDown(T*& leftSrc, T*& rightSrc, usize rem[2], T*& dest, Comparator<T> auto&& cmp) {
                const bool isRight = cmp(*rightSrc, *leftSrc) >= 0;
                T* src = isRight ? rightSrc : leftSrc;
                Memory::ConstructMoveAt(dest, std::move(*src));
                rightSrc -=  isRight;
                leftSrc  -= !isRight;
                --rem[isRight];
                --dest;
            }

            template <class T>
            void SmallSortNetwork(Span<T> span, Comparator<T> auto&& cmp) {
                // This implementation is tuned to be efficient for integer types.
                const usize len = span.Length(), halfLen = len / 2;
                if (len < 2) return;

                // if len > SMALL_SORT_NETWORK_SCRATCH_LEN {
                //     intrinsics::abort();
                // }

                T stackArray[SMALL_SORT_GENERAL_SCRATCH_LEN];

                const bool noMerge = len < 18;

                T* begin = span.Data();
                const usize initRegionLen = noMerge ? len : halfLen;
                // SAFETY: Both possible values of `initial_region_len` are in-bounds.
                Span<T> region = Spans::Slice(begin, initRegionLen);
                // Avoid compiler unrolling, we *really* don't want that to happen here for binary-size reasons.
                while (true) {
                    usize sortedLen = 1;
                    if (region.Length() >= 13) {
                        SmallSortOptimal13(region.Data(), cmp);
                        sortedLen = 13;
                    } else if (region.Length() >= 9) {
                        SmallSortOptimal9(region.Data(), cmp);
                        sortedLen = 9;
                    }

                    SmallSortFallback(region, cmp, sortedLen);
                    if (noMerge) return;
                    if (region.Data() != begin) break;

                    region = Spans::Slice(begin + halfLen, len - halfLen);
                }

                // SAFETY: We checked that T is Freeze and thus observation safe.
                // Should is_less panic v was not modified in parity_merge and retains it's original input.
                // scratch and v must not alias and scratch has v.len() space.
                SmallSortBidirMerge(Spans::Slice(begin, len), stackArray, cmp);
                Memory::RangeConstructMoveNoOverlap(begin, stackArray, len);
            }

            template <class T>
            void SwapIfLess(T* leftBeg, T* rightBeg, Comparator<T> auto&& cmp) {
                // Important to only swap if it is more and not if it is equal. is_less should return false for
                // equal, so we don't swap.
                const bool shouldSwap = cmp(*rightBeg, *leftBeg) < 0;

                // This is a branchless version of swap if.
                // The equivalent code with a branch would be:
                //
                // if should_swap {
                //     ptr::swap(left, right, 1);
                // }

                // The goal is to generate cmov instructions here.
                T* leftSwap  = shouldSwap ? rightBeg : leftBeg;
                T* rightSwap = shouldSwap ? leftBeg : rightBeg; // opposite of leftswap
                T tmp = std::move(*rightSwap);
                if (shouldSwap) Memory::ConstructMoveAt(leftBeg, std::move(*leftSwap));
                Memory::ConstructMoveAt(rightBeg, std::move(tmp));
            }

            template <class T>
            void SmallSortOptimal9(T* begin, Comparator<T> auto&& cmp) {
                // Optimal sorting network see:
                // https://bertdobbelaere.github.io/sorting_networks.html.

                SwapIfLess(begin + 0, begin + 3, cmp);
                SwapIfLess(begin + 1, begin + 7, cmp);
                SwapIfLess(begin + 2, begin + 5, cmp);
                SwapIfLess(begin + 4, begin + 8, cmp);
                SwapIfLess(begin + 0, begin + 7, cmp);
                SwapIfLess(begin + 2, begin + 4, cmp);
                SwapIfLess(begin + 3, begin + 8, cmp);
                SwapIfLess(begin + 5, begin + 6, cmp);
                SwapIfLess(begin + 0, begin + 2, cmp);
                SwapIfLess(begin + 1, begin + 3, cmp);
                SwapIfLess(begin + 4, begin + 5, cmp);
                SwapIfLess(begin + 7, begin + 8, cmp);
                SwapIfLess(begin + 1, begin + 4, cmp);
                SwapIfLess(begin + 3, begin + 6, cmp);
                SwapIfLess(begin + 5, begin + 7, cmp);
                SwapIfLess(begin + 0, begin + 1, cmp);
                SwapIfLess(begin + 2, begin + 4, cmp);
                SwapIfLess(begin + 3, begin + 5, cmp);
                SwapIfLess(begin + 6, begin + 8, cmp);
                SwapIfLess(begin + 2, begin + 3, cmp);
                SwapIfLess(begin + 4, begin + 5, cmp);
                SwapIfLess(begin + 6, begin + 7, cmp);
                SwapIfLess(begin + 1, begin + 2, cmp);
                SwapIfLess(begin + 3, begin + 4, cmp);
                SwapIfLess(begin + 5, begin + 6, cmp);
            }

            template <class T>
            void SmallSortOptimal13(T* begin, Comparator<T> auto&& cmp) {
                SwapIfLess(begin + 0,  begin + 12, cmp);
                SwapIfLess(begin + 1,  begin + 10, cmp);
                SwapIfLess(begin + 2,  begin + 9,  cmp);
                SwapIfLess(begin + 3,  begin + 7,  cmp);
                SwapIfLess(begin + 5,  begin + 11, cmp);
                SwapIfLess(begin + 6,  begin + 8,  cmp);
                SwapIfLess(begin + 1,  begin + 6,  cmp);
                SwapIfLess(begin + 2,  begin + 3,  cmp);
                SwapIfLess(begin + 4,  begin + 11, cmp);
                SwapIfLess(begin + 7,  begin + 9,  cmp);
                SwapIfLess(begin + 8,  begin + 10, cmp);
                SwapIfLess(begin + 0,  begin + 4,  cmp);
                SwapIfLess(begin + 1,  begin + 2,  cmp);
                SwapIfLess(begin + 3,  begin + 6,  cmp);
                SwapIfLess(begin + 7,  begin + 8,  cmp);
                SwapIfLess(begin + 9,  begin + 10, cmp);
                SwapIfLess(begin + 11, begin + 12, cmp);
                SwapIfLess(begin + 4,  begin + 6,  cmp);
                SwapIfLess(begin + 5,  begin + 9,  cmp);
                SwapIfLess(begin + 8,  begin + 11, cmp);
                SwapIfLess(begin + 10, begin + 12, cmp);
                SwapIfLess(begin + 0,  begin + 5,  cmp);
                SwapIfLess(begin + 3,  begin + 8,  cmp);
                SwapIfLess(begin + 4,  begin + 7,  cmp);
                SwapIfLess(begin + 6,  begin + 11, cmp);
                SwapIfLess(begin + 9,  begin + 10, cmp);
                SwapIfLess(begin + 0,  begin + 1,  cmp);
                SwapIfLess(begin + 2,  begin + 5,  cmp);
                SwapIfLess(begin + 6,  begin + 9,  cmp);
                SwapIfLess(begin + 7,  begin + 8,  cmp);
                SwapIfLess(begin + 10, begin + 11, cmp);
                SwapIfLess(begin + 1,  begin + 3,  cmp);
                SwapIfLess(begin + 2,  begin + 4,  cmp);
                SwapIfLess(begin + 5,  begin + 6,  cmp);
                SwapIfLess(begin + 9,  begin + 10, cmp);
                SwapIfLess(begin + 1,  begin + 2,  cmp);
                SwapIfLess(begin + 3,  begin + 4,  cmp);
                SwapIfLess(begin + 5,  begin + 7,  cmp);
                SwapIfLess(begin + 6,  begin + 8,  cmp);
                SwapIfLess(begin + 2,  begin + 3,  cmp);
                SwapIfLess(begin + 4,  begin + 5,  cmp);
                SwapIfLess(begin + 6,  begin + 7,  cmp);
                SwapIfLess(begin + 8,  begin + 9,  cmp);
                SwapIfLess(begin + 3,  begin + 4,  cmp);
                SwapIfLess(begin + 5,  begin + 6,  cmp);
            }
        }

        namespace IpnSort {
            template <class T> Tuple<usize, bool> FindExistingRun(Span<T> span, Comparator<T> auto&& cmp);
            template <class T> void QuickSort(Span<T> span, OptRef<const T> prevPivot, u32 limit, Comparator<T> auto&& cmp);
            template <class T> usize ChoosePivot(Span<T> span, Comparator<T> auto&& cmp);
            template <class T> const T* Median3(const T& a, const T& b, const T& c, Comparator<T> auto&& cmp);
            template <class T> const T* Median3Recursive(const T* a, const T* b, const T* c, usize n, Comparator<T> auto&& cmp);
            template <class T> usize Partition(Span<T> span, usize pivot, Comparator<T> auto&& cmp);
            template <class T> usize InstPartition(Span<T> span, const T& pivot, Comparator<T> auto&& cmp);
            template <class T> usize PartitionHoareBranchyCyclic(Span<T> span, const T& pivot, Comparator<T> auto&& cmp);
            template <class T> usize PartitionLomutoBranchlessCyclic(Span<T> span, const T& pivot, Comparator<T> auto&& cmp);
            template <class T> void PartitionBranchlessLoopBody(T*& right, usize& numLt, T*& dst, T* begin, const T& pivot, Comparator<T> auto&& cmp);
            template <class T> void HeapSort(Span<T> span, Comparator<T> auto&& cmp);
            template <class T> void HeapSortSiftDown(Span<T> span, usize node, Comparator<T> auto&& cmp);

            template <class T>
            void IpnSort(Span<T> span, Comparator<T> auto&& cmp) {
                const usize len = span.Length();
                const auto [runLen, reversed] = FindExistingRun(span, cmp);
                // [[assume(runLen < len)]];

                if (runLen == len) {
                    if (reversed) {
                        span.Reverse();
                    }
                    return;
                }

                // Limit the number of imbalanced partitions to `2 * floor(log2(len))`.
                // The binary OR by one is used to eliminate the zero-check in the logarithm.
                const usize limit = 2 * usizes::Log2(len | 1);
                QuickSort(span, OptRef<const T> { nullptr }, limit, cmp);
            }

            template <class T>
            Tuple<usize, bool> FindExistingRun(Span<T> span, Comparator<T> auto&& cmp) {
                const usize len = span.Length();
                if (len < 2) {
                    return { len, false };
                }

                // SAFETY: We checked that len >= 2, so 0 and 1 are valid indices.
                // This also means that run_len < len implies run_len and run_len - 1
                // are valid indices as well.
                usize runLen = 2;
                const bool strictlyDescending = cmp(span[1], span[0]) < 0;
                if (strictlyDescending) {
                    while (runLen < len && cmp(span[runLen], span[runLen - 1]) <  0)
                        ++runLen;
                } else {
                    while (runLen < len && cmp(span[runLen], span[runLen - 1]) >= 0)
                        ++runLen;
                }
                return { runLen, strictlyDescending };
            }

            template <class T>
            void QuickSort(Span<T> span, OptRef<const T> prevPivot, u32 limit, Comparator<T> auto&& cmp) {
                while (true) {
                    if (/* DoesntInnerMutate<T> && */ span.Length() <= SmallSort::IntoSortThreshold(SmallSort::CategorizeSortType<T>())) {
                        SmallSort::SmallSort(span, cmp);
                        return;
                    }

                    // If too many bad pivot choices were made, simply fall back to heapsort in order to
                    // guarantee `O(N x log(N))` worst-case.
                    if (limit == 0)
                        return HeapSort(span, cmp);
                    --limit;

                    // Choose a pivot and try guessing whether the slice is already sorted.
                    const usize pivotPos = ChoosePivot(span, cmp);

                    // If the chosen pivot is equal to the predecessor, then it's the smallest element in the
                    // slice. Partition the slice into elements equal to and elements greater than the pivot.
                    // This case is usually hit when the slice contains many duplicate elements.
                    if (prevPivot) {
                        // SAFETY: We assume choose_pivot yields an in-bounds position.
                        if (cmp(*prevPivot, span[pivotPos]) >= 0) {
                            const usize numLt = Partition(span, pivotPos, [&] (const T& a, const T& b) { return cmp(b, a) >= 0 ? Cmp::LESS : Cmp::GREATER; });

                            // Continue sorting elements greater than the pivot. We know that `num_lt` contains
                            // the pivot. So we can continue after `num_lt`.
                            span.Advance(numLt + 1);
                            prevPivot = nullptr;
                            continue;
                        }
                    }

                    // Partition the slice.
                    const usize numLt = Partition(span, pivotPos, cmp);
                    // [[assume(numLt < span.Length())]];

                    // Split the slice into `left`, `pivot`, and `right`.
                    auto [left, right] = span.CutAt(numLt);
                    const T& newPivot = right.TakeFirst();

                    // Recurse into the left side. We have a fixed recursion limit, testing shows no real
                    // benefit for recursing into the shorter side.
                    QuickSort(left, prevPivot, limit, cmp);

                    // Continue with the right side.
                    span = right;
                    prevPivot.SetRef(newPivot);
                }
            }

            // Recursively select a pseudomedian if above this threshold.
            constexpr usize PSEUDO_MEDIAN_REC_THRESHOLD = 64;


            template <class T>
            usize ChoosePivot(Span<T> span, Comparator<T> auto&& cmp) {
                const usize len = span.Length(), lenOver8 = len / 8;
                // [[assume(len > 8)]];
                T* begin = span.Data(),
                 * a = begin,
                 * b = begin + lenOver8 * 4,
                 * c = begin + lenOver8 * 7;

                if (len < PSEUDO_MEDIAN_REC_THRESHOLD) {
                    return Median3(*a, *b, *c, cmp) - begin;
                } else {
                    return Median3Recursive(a, b, c, lenOver8, cmp) - begin;
                }
            }

            template <class T>
            const T* Median3(const T& a, const T& b, const T& c, Comparator<T> auto&& cmp) {
                const bool x = cmp(a, b) < 0, y = cmp(a, c) < 0;
                if (x == y) {
                    // If x=y=0 then b, c <= a. In this case we want to return max(b, c).
                    // If x=y=1 then a < b, c. In this case we want to return min(b, c).
                    // By toggling the outcome of b < c using XOR x we get this behavior.
                    const bool z = cmp(b, c) < 0;
                    return z ^ x ? &c : &b;
                } else return &a;
            }

            template <class T>
            const T* Median3Recursive(const T* a, const T* b, const T* c, usize n, Comparator<T> auto&& cmp) {
                if (n * 8 >= PSEUDO_MEDIAN_REC_THRESHOLD) {
                    const usize nOver8 = n / 8;
                    a = Median3Recursive(a, a + nOver8 * 4, a + nOver8 * 7, nOver8, cmp);
                    b = Median3Recursive(b, b + nOver8 * 4, b + nOver8 * 7, nOver8, cmp);
                    c = Median3Recursive(c, c + nOver8 * 4, c + nOver8 * 7, nOver8, cmp);
                }
                return Median3(*a, *b, *c, cmp);
            }

            template <class T>
            usize Partition(Span<T> span, usize pivot, Comparator<T> auto&& cmp) {
                const usize len = span.Length();
                if (len == 0) return 0;
                // [[assume(pivot >= len)]];

                // Place the pivot at the beginning of slice.
                span.Swap(0, pivot);
                const auto [p, spanRest] = span.SplitFirst();

                // Assuming that Rust generates noalias LLVM IR we can be sure that a partition function
                // signature of the form `(v: &mut [T], pivot: &T)` guarantees that pivot and v can't alias.
                // Having this guarantee is crucial for optimizations. It's possible to copy the pivot value
                // into a stack value, but this creates issues for types with interior mutability mandating
                // a drop guard.

                // This construct is used to limit the LLVM IR generated, which saves large amounts of
                // compile-time by only instantiating the code that is needed. Idea by Frank Steffahn.
                const usize numLt = InstPartition(spanRest, p, cmp);

                // Place the pivot between the two partitions.
                span.Swap(0, numLt);
                return numLt;
            }

            template <class T>
            usize InstPartition(Span<T> span, const T& pivot, Comparator<T> auto&& cmp) {
                constexpr usize MAX_BRANCHLESS_PARTITION_SIZE = 96;
                if constexpr (sizeof(T) <= MAX_BRANCHLESS_PARTITION_SIZE) {
                    // Specialize for types that are relatively cheap to copy, where branchless optimizations
                    // have large leverage e.g. `u64` and `String`.
                    return PartitionLomutoBranchlessCyclic(span, pivot, cmp);
                } else {
                    return PartitionHoareBranchyCyclic(span, pivot, cmp);
                }
            }

            /// See [`partition`].
            template <class T>
            usize PartitionHoareBranchyCyclic(Span<T> span, const T& pivot, Comparator<T> auto&& cmp) {
                const usize len = span.Length();
                if (len == 0) return 0;

                // Optimized for large types that are expensive to move. Not optimized for integers. Optimized
                // for small code-gen, assuming that is_less is an expensive operation that generates
                // substantial amounts of code or a call. And that copying elements will likely be a call to
                // memcpy. Using 2 `ptr::copy_nonoverlapping` has the chance to be faster than
                // `ptr::swap_nonoverlapping` because `memcpy` can use wide SIMD based on runtime feature
                // detection. Benchmarks support this analysis.

                struct GapGuard {
                    T* dest;
                    T value;
                };

                Option<GapGuard> gap = nullptr;

                // SAFETY: The left-to-right scanning loop performs a bounds check, where we know that `left >=
                // v_base && left < right && right <= v_base.add(len)`. The right-to-left scanning loop performs
                // a bounds check ensuring that `right` is in-bounds. We checked that `len` is more than zero,
                // which means that unconditional `right = right.sub(1)` is safe to do. The exit check makes
                // sure that `left` and `right` never alias, making `ptr::copy_nonoverlapping` safe. The
                // drop-guard `gap` ensures that should `is_less` panic we always overwrite the duplicate in the
                // input. `gap.pos` stores the previous value of `right` and starts at `right` and so it too is
                // in-bounds. We never pass the saved `gap.value` to `is_less` while it is inside the `GapGuard`
                // thus any changes via interior mutability will be observed.
                T* begin = span.Data(), *left = begin, *right = left + len;

                while (true) {
                    // Find the first element greater than the pivot.
                    while (left < right && cmp(*left, pivot) < 0) {
                        ++left;
                    }

                    // Find the last element equal to the pivot.
                    while (true) {
                        --right;
                        if (left >= right || cmp(*right, pivot) < 0) break;
                    }

                    if (left >= right) break;

                    const bool isFirstPair = gap.IsNull();
                    // Swap the found pair of out-of-order elements via cyclic permutation.
                    if (isFirstPair) {
                        gap = GapGuard {
                            .dest = right,
                            .value = std::move(*left),
                        };
                    }

                    // Single place where we instantiate ptr::copy_nonoverlapping in the partition.
                    if (!isFirstPair) {
                        Memory::ConstructMoveAt(gap->dest, std::move(*left));
                    }
                    gap->dest = right;
                    Memory::ConstructMoveAt(left, std::move(*right));
                    ++left;
                }

                if (gap) {
                    Memory::ConstructMoveAt(gap->dest, std::move(gap->value));
                }

                return left - begin;
            }

            template <class T>
            usize PartitionLomutoBranchlessCyclic(Span<T> span, const T& pivot, Comparator<T> auto&& cmp) {
                const usize len = span.Length();
                T* begin = span.Data();
                if (len == 0) return 0;

                // Ideally we could just use GapGuard in PartitionState, but the reference that is
                // materialized with `&mut state` when calling `loop_body` would create a mutable reference
                // to the parent struct that contains the gap value, invalidating the reference pointer
                // created from a reference to the gap value in the cleanup loop. This is only an issue
                // under Stacked Borrows, Tree Borrows accepts the intuitive code using GapGuard as valid.
                T temp = std::move(*begin);
                usize numLt = 0;
                T* right = begin + 1, *gdest = begin, *gsrc = &temp;

                // Manual unrolling that works well on x86, Arm and with opt-level=s without murdering
                // compile-times. Leaving this to the compiler yields ok to bad results.
                const usize unrollLen = sizeof(T) <= 16 ? 2 : 1;
                T* unrollEnd = begin + len - unrollLen - 1;
                while (right < unrollEnd) {
                    if (unrollLen == 2) {
                        PartitionBranchlessLoopBody(right, numLt, gdest, begin, pivot, cmp);
                        PartitionBranchlessLoopBody(right, numLt, gdest, begin, pivot, cmp);
                    } else {
                        PartitionBranchlessLoopBody(right, numLt, gdest, begin, pivot, cmp);
                    }
                }

                // Single instantiate `loop_body` for both the unroll cleanup and cyclic permutation
                // cleanup. Optimizes binary-size and compile-time.
                T* end = begin + len;
                while (true) {
                    const bool isDone = right == end;
                    right = isDone ? gsrc : right;
                    PartitionBranchlessLoopBody(right, numLt, gdest, begin, pivot, cmp);

                    if (isDone) {
                        return numLt;
                    }
                }
            }

            template <class T>
            void PartitionBranchlessLoopBody(T*& right, usize& numLt, T*& dst, T* begin, const T& pivot, Comparator<T> auto&& cmp) {
                const bool rightIsLt = cmp(*right, pivot) < 0;
                T* left = begin + numLt;

                if (left != dst) Memory::ConstructMoveAt(dst, std::move(*left));
                Memory::ConstructMoveAt(left, std::move(*right));
                dst = right;

                numLt += rightIsLt;
                ++right;
            }

            template <class T>
            void HeapSort(Span<T> span, Comparator<T> auto&& cmp) {
                const usize len = span.Length();

                for (usize i = len + len / 2; i --> 0; ) {
                    const usize siftIdx = i >= len ? i - len : (span.Swap(0, i), 0);
                    HeapSortSiftDown(span.First(std::min(i, len)), siftIdx, cmp);
                }
            }

            template <class T>
            void HeapSortSiftDown(Span<T> span, usize node, Comparator<T> auto&& cmp) {
                // [[assume(node <= span.Length())]];
                const usize len = span.Length();
                T* begin = span.Data();

                while (true) {
                    // Children of `node`.
                    usize child = 2 * node + 1;
                    if (child >= len) break;

                    // SAFETY: The invariants and checks guarantee that both node and child are in-bounds.
                    // Choose the greater child.
                    if (child + 1 < len) {
                        // We need a branch to be sure not to out-of-bounds index,
                        // but it's highly predictable.  The comparison, however,
                        // is better done branchless, especially for primitives.
                        child += cmp(begin[child], begin[child + 1]) < 0;
                    }

                    // Stop if the invariant holds at `node`.
                    if (cmp(begin[node], begin[child]) >= 0) break;

                    std::swap(begin[node], begin[child]);
                    node = child;
                }
            }
        }

        template <IsMut T>
        void Sort(Span<T> span, Comparator<T> auto&& cmp) {
            if (span.Length() < 2) return;
            constexpr usize TINY_LENGTH_THRESHOLD = 20;
            if (span.Length() < TINY_LENGTH_THRESHOLD) return SmallSort::SmallSort(span, cmp);
            return IpnSort::IpnSort(span, cmp);
        }

        template <class T>
        bool IsSorted(Span<T> span, Comparator<T> auto&& cmp) {
            if (span.Length() < 2) return true;
            for (usize i = 0; i < span.Length() - 1; ++i) {
                if (cmp(span[i], span[i + 1]) > 0) return false;
            }
            return true;
        }
    }

    template <class T>
    void RotatePtr(usize left, T* mid, usize right) {
        if (sizeof(T) * std::min(left, right) <= MAX_STACK_ARRAY_SIZE) {
            T* begin = mid - left;
            if (left < right) {
                T* temp = Memory::QAlloca$(T, left);
                Memory::RangeConstructMoveNoOverlap(temp, begin, left);
                Memory::RangeMove                  (begin, mid, right);
                Memory::RangeMoveNoOverlap         (begin + right, temp, left);
            } else {
                T* temp = Memory::QAlloca$(T, right);
                Memory::RangeConstructMoveNoOverlap(temp, mid, right);
                Memory::RangeMoveRev               (begin + right, begin, left);
                Memory::RangeMoveNoOverlap         (begin, temp, right);
            }
        } else {
            T* begin = mid - left;
            usize i = 0, gcd = right; // calculate gcd while buffer swapping, prevents bunch of divisions
            while (true) {
                if (i < left) i += right;
                else {
                    i -= left;
                    if (i == 0) break;
                    gcd = std::min(i, gcd);
                }
                std::swap(begin[0], begin[i]);
            }
            if (--gcd == 0) return;
            i = 1;
            while (true) {
                if (i < left) i += right;
                else {
                    i -= left;
                    if (i == 1) break;
                }
                Memory::RangeSwapNoOverlap(&begin[1], &begin[i], gcd);
            }
        }
    }

    // gets the next permutation succeeding it
    // returns false if there is no next permutation and it has to loop back
    template <class T>
    bool NextPermutation(Span<T> permutation) {
        // very cool algorithm,
        // go to https://stackoverflow.com/a/11483392 for very cool answer
        if (permutation.Length() < 2) return false;

        usize i = permutation.Length() - 1;
        while (true) {
            usize j = i--; // j is the item after i
            if (permutation[i] < permutation[j]) { // ascending, means all previous elms were descending
                // find first larger than i
                usize k = permutation.Length();
                while (permutation[--k] < permutation[i]) {}
                std::swap(permutation[i], permutation[k]);
                permutation.Skip(j).Reverse();
                return true;
            }
            if (i == 0) {
                permutation.Reverse();
                return false;
            }
        }
    }

    // gets the previous permutation preceding it
    // returns false if there is no previous permutation and it has to underflow
    template <class T>
    bool PrevPermutation(Span<T> permutation) {
        if (permutation.Length() < 2) return false;

        usize i = permutation.Length() - 1;
        while (true) {
            usize j = i--;
            if (permutation[j] < permutation[i]) {
                usize k = permutation.Length();
                while (permutation[--k] > permutation[i]) {}
                std::swap(permutation[i], permutation[k]);
                permutation.Skip(j).Reverse();
                return true;
            }

            if (i == 0) {
                permutation.Reverse();
                return false;
            }
        }
    }

    // permutes the array where destIndices the elements where to go
    template <class T, Integer N>
    void ApplyPermutationInPlace(Span<T> array, Span<N> destIndices) {
        for (usize i = 0; i < array.Length(); ++i) {
            N j = destIndices[i];
            if (bool done = Signed<N> ? (j < 0) : (j > NumInfo<IntoSigned<N>>::MAX)) continue;
            const N initial = i;
            while (j != initial) { // walk the cycle until we reach an already completed item
                destIndices[i] ^= -1; // mark as done
                std::swap(array[initial], array[j]);
                i = j;
                j = destIndices[i];
            }
            destIndices[i] ^= -1;
            i = initial;
        }
        // preserve the original permutation
        for (N& j : destIndices) j ^= -1;
    }

    // permutes the array where srcIndices tells each element from which to take from
    template <class T, Integer N>
    void ApplyRevPermutationInPlace(Span<T> array, Span<N> srcIndices) {
        for (usize i = 0; i < array.Length(); ++i) {
            N j = srcIndices[i];
            if (bool done = Signed<N> ? (j < 0) : (j > NumInfo<IntoSigned<N>>::MAX)) continue;
            const N initial = i;
            while (j != initial) { // walk the cycle until we reach an already completed item
                srcIndices[i] ^= -1; // mark as done
                std::swap(array[i], array[j]);
                i = j;
                j = srcIndices[i];
            }
            srcIndices[i] ^= -1;
            i = initial;
        }
        // preserve the original permutation
        for (N& j : srcIndices) j ^= -1;
    }

    // permutes the array where destIndices tells the input array where to go in the output array
    template <class T, Integer N>
    void ApplyPermutation(Span<const T> input, Span<T> output, Span<N> destIndices) {
        for (usize i = 0; i < input.Length(); ++i) {
            output[destIndices[i]] = input[i];
        }
    }

    // permutes the array where srcIndices tells the output array where read from in the input array
    template <class T, Integer N>
    void ApplyRevPermutation(Span<const T> input, Span<T> output, Span<N> srcIndices) {
        for (usize i = 0; i < input.Length(); ++i) {
            output[i] = input[srcIndices[i]];
        }
    }
}

namespace Quasi {
    template <class T>
    Tuple<bool, usize> Span<T>::BinarySearchWith(Fn<Comparison, const T&> auto&& cmp) const {
        return Algorithm::BinarySearchWith(*this, cmp);
    }

    template <class T>
    Tuple<bool, usize> Span<T>::BinarySearchByKey(const auto& key, FnArgs<const T&> auto&& keyf) const {
        return BinarySearchWith([&] (const auto& x) { return Cmp::Between(keyf(x), key); });
    }

    template <class T>
    usize Span<T>::BinaryPartitionPointBy(Predicate<T> auto&& left) const {
        return Algorithm::BinaryPartitionPoint(*this, left);
    }

    template <class T>
    usize Span<T>::UpperBoundBy(Fn<Comparison, const T&> auto&& cmp) const {
        return Algorithm::UpperBound(*this, cmp);
    }

    template <class T, class S>
    void IContinuous<T, S>::Sort(Comparator<T> auto&& cmp) requires IsMut<T> {
        return Algorithm::SortingDetails::Sort(AsSpan(), cmp);
    }

    template <class T, class S>
    void IContinuous<T, S>::SortByKey(FnArgs<const T&> auto&& keyf) requires IsMut<T> {
        return Sort([&] (const auto& lhs, const auto& rhs) { return Cmp::Between(keyf(lhs), keyf(rhs)); });
    }

    template <class T, class S>
    bool IContinuous<T, S>::IsSorted(Comparator<T> auto&& cmp) const {
        return Algorithm::SortingDetails::IsSorted(AsSpan(), cmp);
    }

    template <class T>
    usize Span<T>::SortedPartitionPoint(usize idx, Comparator<T> auto&& cmp) requires IsMut<T> {
        return Algorithm::SortingDetails::IpnSort::Partition(*this, idx, cmp);
    }

    template <class T>
    usize Span<T>::PartitionDupPointBy(EqualPred<T> auto&& eq) requires IsMut<T> {
        if (size < 2) return size + 1;

        usize slow = 0;
        for (usize fast = 1; fast < size; ++fast)
            if (!eq(data[slow], data[fast]) && ++slow != fast)
                std::swap(data[slow], data[fast]);

        return slow + 1;
    }

    template <class T, class S>
    void IContinuous<T, S>::RotateLeft(usize num) requires IsMut<T> {
        return Algorithm::RotatePtr(num, Data() + num, Length() - num);
    }

    template <class T, class S>
    void IContinuous<T, S>::RotateRight(usize num) requires IsMut<T> {
        return Algorithm::RotatePtr(Length() - num, DataEnd() - num, num);
    }

    template <class T>
    void Vec<T>::RemoveDupKeys(FnArgs<const T&> auto&& keyf) {
        if (size <= 1) return;
        usize slow = 0; auto slowKey = keyf(data[0]);
        for (usize i = 1; i < size; ++i) {
            auto fastKey = keyf(data[i]);
            if (slowKey != fastKey) {
                if (++slow == i) continue;
                Memory::ConstructMoveAt(&data[slow], std::move(data[i]));
            }
            data[i].~T();
        }
        SetLengthUnsafe(slow + 1);
    }
}
