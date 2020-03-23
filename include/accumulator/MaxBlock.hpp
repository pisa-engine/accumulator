#pragma once

#include "Paged.hpp"
#include "detail/detail.hpp"
#include <cmath>
#include <vector>

namespace accumulator {

template <typename T>
class MaxBlock: public Paged<T> {
  public:
    explicit MaxBlock(size_t size) : Paged<T>(size)
    {
        m_block_max.resize(Paged<T>::m_clean_flag.size(), 0);
    }

    ACC_ALWAYSINLINE void accumulate(size_t position, T value)
    {
        size_t block = position >> Paged<T>::m_log_block_size;
        if (not Paged<T>::m_clean_flag[block]) {
            m_block_max[block] = 0;
            auto skip = block * Paged<T>::m_block_size;
            std::fill(
                Simple<T>::m_accumulator.begin() + skip,
                Simple<T>::m_accumulator.begin() + skip + Paged<T>::m_block_size,
                0);
            Paged<T>::m_clean_flag[block] = true;
        }
        Simple<T>::accumulate(position, value);
        m_block_max[block] = std::max(m_block_max[block], value);
    }

    using Paged<T>::operator[];
    using Paged<T>::size;
    using Paged<T>::clear;

    template <typename Topk>
    void aggregate(Topk& topk)
    {
        // TODO: need to be checked
        size_t block = 0;
        size_t position = 0;
        for (auto&& clean: Paged<T>::m_clean_flag) {
            if (clean and topk.would_enter(m_block_max[block])) {
                auto skip = block * Paged<T>::m_block_size;
                auto end = std::min(skip + Paged<T>::m_block_size, Paged<T>::size());
                std::for_each(
                    Simple<T>::m_accumulator.begin() + skip,
                    Simple<T>::m_accumulator.begin() + end,
                    [&](auto value) {
                        topk.insert(value, position);
                        position += 1;
                    });
            } else {
                position += Paged<T>::m_block_size;
            }
            block += 1;
        }
    }

  private:
    std::vector<T> m_block_max;
};
}  // namespace accumulator