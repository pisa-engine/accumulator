#define ANKERL_NANOBENCH_IMPLEMENT
#include <algorithm>
#include <nanobench.h>
#include <random>
#include <string>

#include "Counter.hpp"
#include "MaxBlock.hpp"
#include "Paged.hpp"
#include "Simple.hpp"

template <typename Accumulator>
void bench_clear(std::string const& name, size_t iterations)
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

template <typename Accumulator>
void bench_accumulate(std::string const& name, size_t iterations)
{
    auto RandomNumberBetween = [](auto low, auto high) {
        auto randomFunc = [distribution_ = std::uniform_int_distribution(low, high),
                           random_engine_ = std::mt19937{std::random_device{}()}]() mutable {
            return distribution_(random_engine_);
        };
        return randomFunc;
    };
    size_t power = 20;
    size_t size = std::pow(2, power);
    for (auto&& ratio: {1, 10, 50, 80, 100}) {
        size_t elements_size = ratio * size / 100;
        std::vector<size_t> elements(elements_size);
        std::generate(
            elements.begin(), elements.end(), RandomNumberBetween(size_t(0), size_t(size - 1)));
        Accumulator accumulator(size);
        ankerl::nanobench::Bench()
            .minEpochIterations(iterations)
            .run(
                "Accumulate elements in " + name + " accumulator of size 2^{"
                    + std::to_string(power) + "} and ratio " + std::to_string(ratio) + "%",
                [&] {
                    for (auto&& e: elements) {
                        accumulator.accumulate(e, e);
                    }
                })
            .doNotOptimizeAway(accumulator);
    }
}

int main(int argc, char const* argv[])
{
    using namespace accumulator;
    bench_clear<Simple<size_t>>("Simple", 1'000);
    bench_clear<Paged<size_t>>("Paged", 10'000'000);
    bench_clear<MaxBlock<size_t>>("MaxBlock", 10'000'000);

    bench_accumulate<Simple<size_t>>("Simple", 100);
    bench_accumulate<Paged<size_t>>("Paged", 100);
    bench_accumulate<MaxBlock<size_t>>("MaxBlock", 100);
    bench_accumulate<Counter<size_t>>("Counter", 100);
}
