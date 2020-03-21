#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>
#include <string>
#include "Paged.hpp"

int main(int argc, char const* argv[])
{
    for (auto&& power: {16, 18, 20}) {
        auto size = std::pow(2, power);
        accumulator::Paged<size_t> accumulator(size);
        ankerl::nanobench::Bench().minEpochIterations(10'000'000)
            .run("Clear accumulator 2^{"+std::to_string(power)+"}" , [&] { accumulator.clear(); })
            .doNotOptimizeAway(accumulator);
    }
}
