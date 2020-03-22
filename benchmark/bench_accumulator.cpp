#define ANKERL_NANOBENCH_IMPLEMENT
#include "MaxBlock.hpp"
#include "Paged.hpp"
#include "Simple.hpp"
#include <nanobench.h>
#include <string>

template <typename Accumulator>
void perf_clear(std::string const& name, size_t iterations)
{
    for (auto&& power: {16, 18, 20, 25}) {
        auto size = std::pow(2, power);
        Accumulator accumulator(size);
        ankerl::nanobench::Bench()
            .minEpochIterations(iterations)
            .run(
                "Clear " + name + " accumulator of size 2^{" + std::to_string(power) + "}",
                [&] { accumulator.clear(); })
            .doNotOptimizeAway(accumulator);
    }
}

int main(int argc, char const* argv[])
{
    using namespace accumulator;
    perf_clear<Simple<size_t>>("Simple", 1'000);
    perf_clear<Paged<size_t>>("Paged", 10'000'000);
    perf_clear<MaxBlock<size_t>>("MaxBlock", 10'000'000);
}
