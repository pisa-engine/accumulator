file(GLOB BENCH_SOURCES bench_*.cpp)
foreach(BENCH_SRC ${BENCH_SOURCES})
  get_filename_component (BENCH_SRC_NAME ${BENCH_SRC} NAME_WE)
  add_executable(${BENCH_SRC_NAME} ${BENCH_SRC})
    target_link_libraries(${BENCH_SRC_NAME}
        nanobench
        accumulator
    )
  add_test(${BENCH_SRC_NAME} ${BENCH_SRC_NAME})
endforeach(BENCH_SRC)
