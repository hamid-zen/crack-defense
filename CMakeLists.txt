cmake_minimum_required(VERSION 3.18.0)
project(brick-clash LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wall -Wpedantic)
endif()

enable_testing()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
add_subdirectory(src)
add_executable(brick-clash main.cpp)
target_link_libraries(brick-clash PRIVATE gamelib sfml-graphics sfml-audio sfml-window sfml-system sfml-network)
add_subdirectory(test)





