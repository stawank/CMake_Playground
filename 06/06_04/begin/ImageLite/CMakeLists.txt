cmake_minimum_required(VERSION 3.15)
project(ImageLite 
    VERSION 1.0.3
    DESCRIPTION "Simple image processing library and tool"
)

# Enable testing if the option is set
option(IMAGELITE_BUILD_TESTS "Build the test suite" ON)

# Activate CTest support
if(IMAGELITE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Place all executables in the build/bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SAMPLE_IMAGES_DIR ${PROJECT_SOURCE_DIR}/sample_images)

function(add_imagelite_module name)
    add_library(${name} STATIC ${ARGN})

    target_include_directories(${name}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    #if(use_stb)
    #    target_include_directories(${name}
    #        PRIVATE ${PROJECT_SOURCE_DIR}/external/stb
    #    )
    #endif()

    # Add platform-specific definitions - ONLY for this target
    target_compile_definitions(${name} PRIVATE
        $<$<PLATFORM_ID:Windows>:IMAGELITE_WINDOWS>
        $<$<PLATFORM_ID:Linux>:IMAGELITE_LINUX>
        $<$<PLATFORM_ID:Darwin>:IMAGELITE_MACOS>
    )

    # Add compiler-specific warning options - ONLY for this target
    target_compile_options(${name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
        $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
    )

    # Add DEBUG-specific extra warnings and debug info
    target_compile_options(${name} PRIVATE
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:-Wpedantic -g>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-Wpedantic -g>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /Od>
    )

    # Add RELEASE-specific optimizations
    target_compile_options(${name} PRIVATE
        $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O3>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2>
    )
endfunction()

#set_directory_properties(PROPERTIES
#    COMPILE_OPTIONS "$<$<OR:$<CXX_COMPILER_ID:GNU>,#$<CXX_COMPILER_ID:Clang>>:-Wall;-Wextra>;#$<$<CXX_COMPILER_ID:MSVC>:/W4>"
#)

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

# CLI-specific compile options - ONLY affects this executable
target_compile_options(imagelite PRIVATE
    # Extra strict flags for our application code
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -Wconversion -Wshadow>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic -Wconversion -Wshadow>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

# Add debug-specific options
target_compile_options(imagelite PRIVATE
    $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-g -O0>
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /Od /RTC1>
)

# Add release-specific options
target_compile_options(imagelite PRIVATE
    $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O3>
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2>
)

target_include_directories(imagelite
    PRIVATE
        libs/core/include
        libs/filters/include
        ${CMAKE_BINARY_DIR}/include  # Include path for generated headers
)

# Add this before your add_custom_command
find_package(Python REQUIRED COMPONENTS Interpreter)
message(STATUS "Python executable: ${Python_EXECUTABLE}")

# Create the output directory for the generated header
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include/imagelite)

# Generate formats.h
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/include/imagelite/formats.h
    COMMAND ${Python_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/generate_formats.py
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating supported image formats header..."
    VERBATIM
)

# Create a target for the generated file
add_custom_target(generate_formats
    DEPENDS ${CMAKE_BINARY_DIR}/include/imagelite/formats.h
)

# Ensure the header is generated before compilation
add_dependencies(imagelite generate_formats)

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

# In the top-level CMakeLists.txt
set_target_properties(imagelite PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release"
)

# Platform detection
message(STATUS "Detecting platform...")
if(WIN32)
    message(STATUS "Platform: Windows")
elseif(APPLE)
    message(STATUS "Platform: macOS, iOS, tvOS, visionOS or watchOS")
elseif(UNIX AND NOT APPLE)
    message(STATUS "Platform: Linux")
else()
    message(STATUS "Platform: Unknown")
endif()

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose build type: Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif()

# Print the current build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")