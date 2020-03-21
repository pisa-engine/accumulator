#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <cassert>
#include <random>
#include <vector>

#include "Paged.hpp"
#include <rapidcheck.h>

using namespace accumulator;

template <typename Accumulator, typename T>
static void test(Accumulator& accumulator, std::vector<T> const& elements)
{
    for (size_t position = 0; position < accumulator.size(); ++position) {
        REQUIRE(accumulator[position] == 0);
    }
    for (auto&& i: elements) {
        accumulator[i] = i;
    }
    std::unordered_set<T> elements_set(elements.begin(), elements.end());
    for (size_t position = 0; position < accumulator.size(); ++position) {
        if (elements_set.count(position)) {
            REQUIRE(accumulator[position] == position);
        } else {
            REQUIRE(accumulator[position] == 0);
        }
    }
}

TEST_CASE("Paged")
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
        Paged<size_t> accumulator(64);
        auto elements = shuffled_iota_vector(64);
        test(accumulator, elements);
    }
    SECTION("Only 1 accumulator in last block")
    {
        Paged<size_t> accumulator(65);
        auto elements = shuffled_iota_vector(65);
        test(accumulator, elements);
    }
    SECTION("Missing 1 accumulator in last block")
    {
        Paged<size_t> accumulator(63);
        auto elements = shuffled_iota_vector(63);
        test(accumulator, elements);
    }
    SECTION("Single block")
    {
        Paged<size_t> accumulator(1);
        auto elements = shuffled_iota_vector(1);
        test(accumulator, elements);
    }
    SECTION("Random")
    {
        rc::check([]() {
            auto elements = *rc::gen::unique<std::vector<size_t>>(rc::gen::inRange(0, 1'000'000));
            if (elements.size()) {
                std::sort(elements.begin(), elements.end());
                Paged<size_t> accumulator(elements.back() + 1);
                test(accumulator, elements);
            }
        });
    }
}
