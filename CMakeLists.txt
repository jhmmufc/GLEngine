# Require a fairly up to date cmake
cmake_minimum_required(VERSION 3.2)

# Add Hunter support for 3rd parties
include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.108.tar.gz"
    SHA1 "56cf9f1d52296373dbcc0d0c9c2b5526a0815019"
)

# Create project using C++
project(gl_engine VERSION 1.0.0 LANGUAGES C CXX)

if (CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

  if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif() 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

# Include Catch as an imported target
hunter_add_package(Catch)
find_package(Catch CONFIG REQUIRED)

# Include Glew as an imported target
hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)

# Include SDL as an imported target
hunter_add_package(SDL2)
find_package(SDL2 CONFIG REQUIRED)

#Include GLM as an imported target
hunter_add_package(glm)
find_package(glm REQUIRED)

enable_testing()

add_subdirectory(src)
add_subdirectory(test_game)
add_subdirectory(unit_test)
