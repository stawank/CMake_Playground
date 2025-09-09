cmake_minimum_required(VERSION 3.15)
project (ImageLite)

# Place all executables in the build/bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(libs/core)
add_subdirectory(libs/filters)

add_executable(imagelite
  apps/cli/src/main.cpp
)

target_link_libraries(imagelite
    PRIVATE
        imagelite_core
        imagelite_filters
)

target_include_directories(imagelite
    PRIVATE
        libs/core/include
        libs/filters/include
)
