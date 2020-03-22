#pragma once

#include "detail/detail.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

namespace accumulator {

template <typename T>
class Simple {
    static_assert(std::is_arithmetic<T>::value, "Accumulator requires arithmetic elements.");

  public:
    explicit Simple(size_t size) { accumulator.resize(size); }

    void accumulate(size_t position, T value) { accumulator[position] = value; }

    [[nodiscard]] ACC_ALWAYSINLINE T const& operator[](size_t position) const
    {
        return accumulator[position];
    }

    [[nodiscard]] ACC_ALWAYSINLINE size_t size() const { return accumulator.size(); }

    void clear() { std::fill(accumulator.begin(), accumulator.end(), 0); }

    template <typename Topk>
    void aggregate(Topk& topk)
    {
        size_t position = 0u;
        std::for_each(accumulator.begin(), accumulator.end(), [&](auto value) {
            topk.insert(value, position);
            position += 1;
        });
    }

  protected:
    std::vector<T> accumulator;
};
}  // namespace accumulator