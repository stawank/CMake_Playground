add_imagelite_module(imagelite_filters
    src/filters.cpp
)

target_link_libraries(imagelite_filters
    PUBLIC imagelite_core
)