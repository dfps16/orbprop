cmake_minimum_required(VERSION 3.20)
project(orbprop LANGUAGES CXX)

# --- Language settings -------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- The library: all propagator code lives here ----------------------
add_library(orbprop
    src/dynamics.cpp
)
target_include_directories(orbprop PUBLIC include)
target_compile_options(orbprop PRIVATE -Wall -Wextra -Wpedantic)

# --- Unit tests --------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests
    tests/test_dynamics.cpp
)
target_link_libraries(tests PRIVATE orbprop Catch2::Catch2WithMain)

enable_testing()
include(Catch)
catch_discover_tests(tests)