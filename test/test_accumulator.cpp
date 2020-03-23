#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <algorithm>
#include <nanobench.h>

#include <cassert>
#include <random>
#include <vector>

#include "Counter.hpp"
#include "MaxBlock.hpp"
#include "Paged.hpp"
#include "Simple.hpp"

#include <rapidcheck.h>

using namespace accumulator;

template <typename T>
struct TopkMock {
    explicit TopkMock(size_t k) : m_k(k) {}

    void insert(T const& v, size_t const& p)
    {
        values.push_back(v);
        ankerl::nanobench::doNotOptimizeAway(p);
    }
    bool would_enter(T const& v) { return true; }

    auto topk(size_t end)
    {
        std::sort(values.begin(), values.end(), std::greater<T>());
        return std::vector<T>(values.begin(), values.begin() + end);
    }

    std::vector<T> values;
    size_t m_k;
};

template <typename Accumulator>
void check_is_empty(Accumulator const& accumulator)
{
    for (size_t position = 0; position < accumulator.size(); ++position) {
        REQUIRE(accumulator[position] == 0);
    }
}

template <typename Accumulator, typename T>
static void test(Accumulator& accumulator, std::vector<T>& elements)
{
    check_is_empty(accumulator);
    for (auto&& i: elements) {
        accumulator.accumulate(i, i);
    }
    std::unordered_set<T> elements_set(elements.begin(), elements.end());
    for (size_t position = 0; position < accumulator.size(); ++position) {
        if (elements_set.count(position)) {
            REQUIRE(accumulator[position] == position);
        } else {
            REQUIRE(accumulator[position] == 0);
        }
    }

    TopkMock<T> topk(10);
    accumulator.aggregate(topk);
    std::sort(elements.begin(), elements.end(), std::greater<T>());
    auto end = std::min(elements.size(), topk.m_k);
    CHECK(topk.topk(end) == std::vector<T>(elements.begin(), elements.begin() + end));

    accumulator.clear();
    check_is_empty(accumulator);
}

template <typename Accumulator>
void perf_test()
{
    auto shuffled_iota_vector = [](size_t size) {
        std::vector<size_t> elements(size);
        std::iota(elements.begin(), elements.end(), 0);
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(elements.begin(), elements.end(), g);
        return elements;
    };
    SECTION("64 accumulators")
    {
        Accumulator accumulator(64);
        auto elements = shuffled_iota_vector(64);
        test(accumulator, elements);
    }
    SECTION("Only 1 accumulator in last block")
    {
        Accumulator accumulator(65);
        auto elements = shuffled_iota_vector(65);
        test(accumulator, elements);
    }
    SECTION("Missing 1 accumulator in last block")
    {
        Accumulator accumulator(63);
        auto elements = shuffled_iota_vector(63);
        test(accumulator, elements);
    }
    SECTION("Single block")
    {
        Accumulator accumulator(1);
        auto elements = shuffled_iota_vector(1);
        test(accumulator, elements);
    }
    SECTION("Random")
    {
        rc::check([]() {
            auto elements = *rc::gen::unique<std::vector<size_t>>(rc::gen::inRange(0, 1'000'000));
            if (elements.size()) {
                std::sort(elements.begin(), elements.end());
                Accumulator accumulator(elements.back() + 1);
                test(accumulator, elements);
            }
        });
    }
}

TEST_CASE("Simple")
{
    perf_test<Simple<size_t>>();
}

TEST_CASE("Paged")
{
    perf_test<Paged<size_t>>();
}

TEST_CASE("MaxBlock")
{
    perf_test<MaxBlock<size_t>>();
}

TEST_CASE("Counter")
{
    perf_test<Counter<size_t>>();
}