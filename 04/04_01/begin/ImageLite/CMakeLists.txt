cmake_minimum_required(VERSION 3.15)
project(ImageLite 
    VERSION 1.0.3
    DESCRIPTION "Simple image processing library and tool"
)

# Place all executables in the build/bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SAMPLE_IMAGES_DIR ${PROJECT_SOURCE_DIR}/sample_images)

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

# Create a custom command that generates a detailed build info file
add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/build_info.txt"

    COMMAND ${CMAKE_COMMAND} -E echo "ImageLite Build Information" > "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "CMake Version: ${CMAKE_VERSION}" >> "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}" >> "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "System: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}" >> "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "Project Version: ${PROJECT_VERSION}" >> "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "Project Description: ${PROJECT_DESCRIPTION}" >> "${CMAKE_BINARY_DIR}/build_info.txt"
    
    COMMENT "Creating detailed build information file"
    VERBATIM
)

# Create a custom target that depends on the build info file
add_custom_target(
    build_info ALL
    DEPENDS "${CMAKE_BINARY_DIR}/build_info.txt"
)

# Pre-build command to copy README.md to build/bin and create a build/temp folder
add_custom_command(
    TARGET imagelite
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_SOURCE_DIR}/README.md"
            "${CMAKE_BINARY_DIR}/bin/README.md"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/temp"
    COMMENT "Setting up build environment"
)

# Post-build command to clean up
add_custom_command(
    TARGET imagelite
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning up..."
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${CMAKE_BINARY_DIR}/temp"
    COMMENT "Post-build cleanup"
)


add_custom_target(run
  COMMAND imagelite blur ${SAMPLE_IMAGES_DIR}/input.jpg ${SAMPLE_IMAGES_DIR}/blurred_output.jpg 5
  DEPENDS imagelite
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} 
  COMMENT "Generating a blurred version of the source image using imagelite."
)