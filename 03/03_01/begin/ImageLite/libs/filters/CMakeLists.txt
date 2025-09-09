add_imagelite_module (imagelite_filters FALSE 
    src/filters.cpp   

)

target_link_libraries(imagelite_filters 
PUBLIC imagelite_core 
)