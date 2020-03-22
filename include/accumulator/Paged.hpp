#pragma once

#include "Simple.hpp"
#include "detail/detail.hpp"
#include <cmath>
#include <vector>
#include <cstdint>

namespace accumulator {

template <typename T>
class Paged: public Simple<T> {
    static_assert(std::is_arithmetic<T>::value, "Accumulator requires arithmetic elements.");

  public:
    explicit Paged(size_t size)
        : Simple<T>(size),
          m_default_value(0),
          m_log_block_size(std::floor(std::log2(size_t(sqrt(size))))),
          m_block_size(size_t(1) << m_log_block_size)
    {
        auto blocks_number = std::ceil(float(size) / m_block_size);
        m_clean_flag.resize(blocks_number, true);
    }

    void accumulate(size_t position, T value)
    {
        size_t block = position >> m_log_block_size;
        if (not m_clean_flag[block]) {
            auto skip = block * m_block_size;
            std::fill(
                Simple<T>::accumulator.begin() + skip,
                Simple<T>::accumulator.begin() + skip + m_block_size,
                0);
            m_clean_flag[block] = true;
        }
        Simple<T>::accumulate(position, value);
    }

    [[nodiscard]] ACC_ALWAYSINLINE T const& operator[](size_t position) const
    {
        size_t block = position >> m_log_block_size;
        if (not m_clean_flag[block]) {
            return m_default_value;
        }
        return Simple<T>::operator[](position);
    }

    using Simple<T>::size;

    void clear() { std::fill(m_clean_flag.begin(), m_clean_flag.end(), false); }

    template <typename Topk>
    void aggregate(Topk& topk)
    {
        // TODO: need to be checked
        size_t block = 0;
        size_t position = 0;
        for (auto&& clean: m_clean_flag) {
            if (clean) {
                auto skip = block * m_block_size;
                auto end = std::max(skip + m_block_size, size());
                std::for_each(
                    Simple<T>::accumulator.begin() + skip,
                    Simple<T>::accumulator.begin() + end,
                    [&](auto value) {
                        topk.insert(value, position);
                        position += 1;
                    });
            } else {
                position += m_block_size;
            }
            block += 1;
        }
    }

  protected:
    T m_default_value;
    std::vector<uint8_t> m_clean_flag;
    size_t m_log_block_size;
    size_t m_block_size;
};
}  // namespace accumulator