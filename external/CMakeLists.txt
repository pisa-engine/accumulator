EXECUTE_PROCESS(COMMAND git submodule update --init
                WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
                OUTPUT_QUIET
        )

# Add Catch
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Catch2)
# Add RapidCheck
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rapidcheck)
target_compile_options(rapidcheck PRIVATE -Wno-error=all)

add_library(nanobench INTERFACE)
target_include_directories(nanobench INTERFACE ${PROJECT_SOURCE_DIR}/external/nanobench/src/include)
