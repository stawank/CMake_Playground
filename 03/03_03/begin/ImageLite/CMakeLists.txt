cmake_minimum_required(VERSION 3.15)
project (ImageLite)

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