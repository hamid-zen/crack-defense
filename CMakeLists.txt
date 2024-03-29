cmake_minimum_required(VERSION 3.18.0)
project(crack-attack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wall -Wpedantic)
endif()

# Recherche de la bibliothèque ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

enable_testing()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
add_subdirectory(src)

add_executable(crack-attack main.cpp)
# Lier la bibliothèque ncurses
target_link_libraries(crack-attack PRIVATE gamelib ${CURSES_LIBRARIES})

add_subdirectory(test)
