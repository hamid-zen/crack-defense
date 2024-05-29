include(AddCatch2)

add_executable(
  unit_tests
  test_calc.cpp
)
target_link_libraries(
  unit_tests PRIVATE gamelib sfml-graphics sfml-audio sfml-window sfml-system sfml-network Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)
