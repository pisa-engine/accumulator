#pragma once

#include "Simple.hpp"
#include <algorithm>
#include <vector>

namespace accumulator {

template <typename T>
struct Counter: public Simple<T> {
    static constexpr size_t cycle = size_t(1) << 8;

    Counter(std::size_t size) : Simple<T>(2 * size), m_default_value(0) {}

    ACC_ALWAYSINLINE void accumulate(size_t position, T value)
    {
        auto pos = position << 1;
        if (Simple<T>::operator[](pos) != m_counter) {
            Simple<T>::accumulate(pos, m_counter);
        }
        Simple<T>::accumulate(pos + 1, value);
    }

    [[nodiscard]] ACC_ALWAYSINLINE T const& operator[](size_t position) const
    {
        auto pos = position << 1;
        if (Simple<T>::operator[](pos) == m_counter) {
            return Simple<T>::operator[](pos + 1);
        } else {
            return m_default_value;
        }
    }

    template <typename Topk>
    void aggregate(Topk& topk)
    {
        size_t position = 0;
        for (size_t pos = 0; pos < Simple<T>::m_accumulator.size(); pos += 2) {
            if (Simple<T>::operator[](pos) == m_counter) {
                topk.insert(Simple<T>::operator[](pos + 1), position);
            }
        }
    }

    [[nodiscard]] ACC_ALWAYSINLINE size_t size() const { return Simple<T>::size() / 2; }

    ACC_ALWAYSINLINE void clear()
    {
        m_counter = (m_counter + 1) % cycle;
        if (m_counter == 0) {
            Simple<T>::clear();
        }
    }

  private:
    T m_default_value;
    uint8_t m_counter{};
};
}  // namespace accumulator
