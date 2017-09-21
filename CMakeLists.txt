# Require a fairly up to date cmake
cmake_minimum_required(VERSION 3.8)

# Add Hunter support for 3rd parties
include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.108.tar.gz"
    SHA1 "56cf9f1d52296373dbcc0d0c9c2b5526a0815019"
)

# Create project using C++
project(gl_engine VERSION 1.0.0 LANGUAGES CXX)

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
