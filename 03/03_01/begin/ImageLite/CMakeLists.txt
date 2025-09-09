## Important file in project
cmake_minimum_required(VERSION 3.10)
project(ImageLite 
    VERSION 1.0
    DESCRIPTION "CMake build and scripting"
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SAMPLE_IMAGES_DIR ${PROJECT_SOURCE_DIR}/sample_images)
add_subdirectory(libs/core)
add_subdirectory(libs/filters)


add_executable(imagelite 
    apps/cli/src/main.cpp)

add_custom_target(run
    COMMAND imagelite grayscale ${SAMPLE_IMAGES_DIR}/input.jpg ${SAMPLE_IMAGES_DIR}/output.jpg 
    DEPENDS imagelite
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the cli tool with sample arguments"
)

add_custom_target(runblur
    COMMAND imagelite blur ${SAMPLE_IMAGES_DIR}/input.jpg ${SAMPLE_IMAGES_DIR}/outputblurred.jpg 5
    DEPENDS imagelite
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the cli tool with sample arguments"
)

add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "Imagelite Build Information" > "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "CMake Version: ${CMAKE_VERSION}" >> "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}" >> 
    "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "System: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}" >> 
    "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "Project Version: ${PROJECT_VERSION} " >> 
    "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "Project Description: ${PROJECT_DESCRIPTION} " >> 
    "${CMAKE_BINARY_DIR}/build_info.txt"
    COMMENT "Creating detailed build information file"
    VERBATIM
)

add_custom_target(build_info ALL 
    DEPENDS ${CMAKE_BINARY_DIR}/build_info.txt    
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