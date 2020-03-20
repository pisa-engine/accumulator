cmake_minimum_required(VERSION 3.0)
project(accumulator CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ACCUMULATORS_ENABLE_TESTING "Enable testing of the library." ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()
MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external)

# Add code coverage
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/CMake-codecov/cmake")
find_package(codecov)
list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/external/*'")

if (USE_SANITIZERS)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif ()

include_directories(include)
add_library(accumulator INTERFACE)
target_include_directories(accumulator INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/accumulator>
)
target_include_directories(accumulator INTERFACE external)

add_subdirectory(benchmark)

if (ACCUMULATORS_ENABLE_TESTING AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
