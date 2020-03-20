#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <cassert>
#include <random>
#include <rapidcheck.h>

#include "Paged.hpp"

using namespace accumulator;

template <typename Accumulator, typename T>
static void test(Accumulator& instance, std::vector<T> const& elements)
{
    for (size_t position = 0; position < instance.size(); ++position) {
        REQUIRE(instance[position] == 0);
    }

    for (const auto& element: elements) {
        instance[element] = element;
    }

    auto elements_set = std::unordered_set(elements.begin(), elements.end());

    for (size_t position = 0; position < instance.size(); ++position) {
        if (elements_set.count(position)) {
            REQUIRE(instance[position] == position);
        } else {
            REQUIRE(instance[position] == 0);
        }
    }
}

TEST_CASE("Paged")
{
    auto shuffled_iota_vector = [](size_t size) {
        std::vector<size_t> elements(size);
        std::iota(elements.begin(), elements.end(), 0);
        std::random_device random_number_generator;
        std::shuffle(elements.begin(), elements.end(), std::knuth_b(random_number_generator()));
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
        rc::check([](std::vector<size_t> elements) {
            std::sort(elements.begin(), elements.end());
            Paged<size_t> accumulator(elements.size() ? 0 : elements.back());
            test(accumulator, elements);
        });
    }
}
