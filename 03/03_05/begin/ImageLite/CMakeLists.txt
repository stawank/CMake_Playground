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

add_custom_target(run
  COMMAND imagelite blur ../../sample_images/input.jpg ../../sample_images/blurred_output.jpg 5
  DEPENDS imagelite
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} 
  COMMENT "Generating a blurred version of the source image using imagelite."
)