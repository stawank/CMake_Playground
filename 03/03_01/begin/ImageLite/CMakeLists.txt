cmake_minimum_required(VERSION 3.10)
project(ImageLite)

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