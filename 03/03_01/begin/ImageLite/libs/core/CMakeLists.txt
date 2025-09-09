
add_library(imagelite_core STATIC 
    src/core.cpp
    src/image.cpp)

target_include_directories(imagelite_core 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/stb)

    