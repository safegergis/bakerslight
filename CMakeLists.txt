cmake_minimum_required(VERSION 3.28)
project(BakersLight LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(FetchContent)

set(SOURCES
    src/main.cpp
    # src/player.cpp
    src/tilemap.cpp)

find_package(SFML COMPONENTS Graphics QUIET)

if (NOT SFML_FOUND)
    message(STATUS "SFML not found. Fetching from source.")
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif()

find_package(EnTT QUIET)

if (NOT EnTT_FOUND)
    message(STATUS "entt not found. Fetching from source.")
    FetchContent_Declare(EnTT
        GIT_REPOSITORY github.com/skypjack/entt.git
        GIT_TAG 3.15.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(EnTT)
endif()

add_executable(main ${SOURCES})
target_compile_features(main PRIVATE cxx_std_17)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE SFML::Graphics EnTT::EnTT)
