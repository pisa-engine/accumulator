#include <cassert>
#include <random>

#include "accumulator_2d.hpp"

using namespace acc;


template <typename ACCUMULATOR_2D>
static void unittest_example(ACCUMULATOR_2D &instance) {

  std::vector<size_t> sequence(instance.size());
  std::iota(sequence.begin(), sequence.end(), 0);
  std::random_device random_number_generator;
  std::shuffle(sequence.begin(), sequence.end(),
               std::knuth_b(random_number_generator()));

  for (const auto &position : sequence) {
    assert(instance[position] == 0);
    instance[position] = position;
    assert(instance[position] == position);
  }

  for (size_t element = 0; element < instance.size(); element++)
    assert(instance[element] == element);
}


static void unittest(void) {
  Accumulator2D<size_t> array(64);
  unittest_example(array);


  Accumulator2D<size_t> array_hangover(65);
  unittest_example(array_hangover);

  Accumulator2D<size_t> array_hangunder(63);
  unittest_example(array_hangunder);

  Accumulator2D<size_t> array_one(1);
  unittest_example(array_one);

  puts("Accumulator2D::PASSED");
}
int main(int argc, char const *argv[]) { unittest(); }