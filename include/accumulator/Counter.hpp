#pragma once

#include "Simple.hpp"
#include <algorithm>
#include <vector>

namespace accumulator {

template <typename T>
struct Counter: public Simple<T> {
    static constexpr size_t cycle = size_t(1) << 8;

    Counter(std::size_t size) : Simple<T>(size), m_default_value(0)
    {
        m_descriptor.resize(size, 0);
    }

    ACC_ALWAYSINLINE void accumulate(size_t position, T value)
    {
        if (m_descriptor[position] != m_counter) {
            m_descriptor[position] = m_counter;
        }
        Simple<T>::accumulate(position, value);
    }

    [[nodiscard]] ACC_ALWAYSINLINE T const& operator[](size_t position) const
    {
        if (m_descriptor[position] == m_counter) {
            return Simple<T>::operator[](position);
        } else {
            return m_default_value;
        }
    }

    template <typename Topk>
    void aggregate(Topk& topk)
    {
        size_t position = 0;
        for (auto&& value: Simple<T>::m_accumulator) {
            if (m_descriptor[position] == m_counter) {
                topk.insert(value, position);
            }
            position += 1;
        }
    }

    using Simple<T>::size;

    ACC_ALWAYSINLINE void clear()
    {
        m_counter = (m_counter + 1) % cycle;
        if (m_counter == 0) {
            std::fill(m_descriptor.begin(), m_descriptor.end(), m_counter - 1);
        }
    }

  private:
    T m_default_value;
    std::vector<uint8_t> m_descriptor;
    uint8_t m_counter{};
};  // namespace accumulator
}  // namespace accumulator
