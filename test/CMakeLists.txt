set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/test)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../external/Catch2/contrib)
include(CTest)
include(Catch)

add_executable(test_accumulator test_accumulator.cpp)
target_link_libraries(test_accumulator
Catch2
rapidcheck
accumulator
nanobench
)
catch_discover_tests(test_accumulator TEST_PREFIX "test_accumulator:")

# enable code coverage
add_coverage(test_accumulator)

