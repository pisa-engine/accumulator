#define ANKERL_NANOBENCH_IMPLEMENT
#include <algorithm>
#include <nanobench.h>
#include <random>
#include <string>
#include <cmath>

#include "Counter.hpp"
#include "MaxBlock.hpp"
#include "Paged.hpp"
#include "Simple.hpp"

template <typename T>
struct TopkMock {
    template <typename Value, typename Position>
    ACC_ALWAYSINLINE void insert(Value const& v, Position const& p)
    {
        ankerl::nanobench::doNotOptimizeAway(v);
        ankerl::nanobench::doNotOptimizeAway(p);
    }
    template <typename Value>
    ACC_ALWAYSINLINE bool would_enter(Value const& v)
    {
        if (v >= m_threshold) {
            return true;
        } else {
            return false;
        }
    }
    T m_threshold = 0;
};

auto RandomNumberBetween = [](auto low, auto high) {
    auto randomFunc = [distribution_ = std::uniform_int_distribution(low, high),
                       random_engine_ = std::mt19937{std::random_device{}()}]() mutable {
        return distribution_(random_engine_);
    };
    return randomFunc;
};

template <typename Accumulator>
void bench_clear(std::string const& name, size_t iterations)
{
    for (auto&& power: {16, 18, 20, 25}) {
        auto size = std::pow(2, power);
        Accumulator accumulator(size);
        ankerl::nanobench::Bench().title("Clear")
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
    size_t power = 20;
    size_t size = std::pow(2, power);
    for (auto&& ratio: {1, 10, 50, 80, 100}) {
        size_t elements_size = ratio * size / 100;
        std::vector<size_t> elements(elements_size);
        std::generate(
            elements.begin(), elements.end(), RandomNumberBetween(size_t(0), size_t(size - 1)));
        Accumulator accumulator(size);
        ankerl::nanobench::Bench().title("Accumulate")
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

template <typename Accumulator, typename T>
void bench_aggregate(std::string const& name, size_t iterations)
{
    size_t power = 25;
    size_t size = std::pow(2, power);
    for (auto&& ratio: {1, 10, 50, 80, 100}) {
        size_t elements_size = ratio * size / 100;
        std::vector<size_t> elements(elements_size);
        std::generate(
            elements.begin(), elements.end(), RandomNumberBetween(T(0), T(size - 1)));
        Accumulator accumulator(size);
        for (auto&& e: elements) {
            accumulator.accumulate(e, e);
        }
        std::sort(elements.begin(), elements.end(), std::greater<T>());
        auto end = std::min(elements.size(), size_t(10));
        auto threshold = elements[end];
        ankerl::nanobench::Bench().title("Aggregate")
            .minEpochIterations(iterations)
            .run(
                "Aggregate elements in " + name + " accumulator of size 2^{" + std::to_string(power)
                    + "} and ratio " + std::to_string(ratio) + "%",
                [&] {
                    TopkMock<T> topk;
                    topk.m_threshold = threshold;
                    accumulator.aggregate(topk);
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

    bench_aggregate<Simple<size_t>, size_t>("Simple", 10);
    bench_aggregate<Paged<size_t>, size_t>("Paged", 10);
    bench_aggregate<MaxBlock<size_t>, size_t>("MaxBlock", 10);
    bench_aggregate<Counter<size_t>, size_t>("Counter", 10);
}
