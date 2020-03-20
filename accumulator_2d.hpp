#pragma once

#include <cmath>
#include <vector>
#include "utils.hpp"

namespace acc {

template <typename T> class Accumulator2D {

  static_assert(std::is_arithmetic<T>::value,
                "Accumulator requires arithmetic elements.");

public:
  explicit Accumulator2D(size_t size)
      : m_log_block_size(std::floor(std::log2(sqrt(size)))),
        m_block_size(size_t(1) << m_log_block_size), {
    auto blocks_number = std::ceil(size / m_block_size);
    m_clean_flag.resize(blocks_number, false);
    accumulator.resize(m_block_size * blocks_number);
  }

  [[nodiscard]] __ALWAYSINLINE T &operator[](size_t position) {
    size_t block = position >> m_log_block_size;
    if (not m_clean_flag[block]) {
      auto skip = block * m_block_size;
      std::fill(accumulator.begin() + skip,
                accumulator.begin() + skip + m_block_size, 0);
      m_clean_flag[block] = true;
    }
    return accumulator[position];
  }

  [[nodiscard]] __ALWAYSINLINE size_t size() const {
    return accumulator.size();
  }

  void clear() { std::fill(m_clean_flag.begin(), m_clean_flag.end(), false); }

private:
  std::vector<uint8_t> m_clean_flag;
  std::vector<T> accumulator;
  size_t m_block_size;
  size_t m_log_block_size;
};
} // namespace acc