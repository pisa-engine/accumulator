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
    explicit Simple(size_t size) { m_accumulator.resize(size); }

    ACC_ALWAYSINLINE void accumulate(size_t position, T value) { m_accumulator[position] = value; }

    [[nodiscard]] ACC_ALWAYSINLINE T const& operator[](size_t position) const
    {
        return m_accumulator[position];
    }

    [[nodiscard]] ACC_ALWAYSINLINE size_t size() const { return m_accumulator.size(); }

    ACC_ALWAYSINLINE void clear() { std::fill(m_accumulator.begin(), m_accumulator.end(), 0); }

    template <typename Topk>
    void aggregate(Topk& topk)
    {
        size_t position = 0u;
        std::for_each(m_accumulator.begin(), m_accumulator.end(), [&](auto value) {
            topk.insert(value, position);
            position += 1;
        });
    }

  protected:
    std::vector<T> m_accumulator;
};
}  // namespace accumulator