
add_library(imagelite_filters STATIC 
    src/filters.cpp)

target_include_directories(imagelite_filters 
    PUBLIC 
    $(CMAKE_CURRENT_SOURCE_DIR)/include)

target_link_libraries(imagelite_filters 
PUBLIC imagelite_core 
)