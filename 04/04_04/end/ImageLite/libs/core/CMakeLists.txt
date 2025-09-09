add_imagelite_module(imagelite_core TRUE
    src/core.cpp
    src/image.cpp
)

set_target_properties(imagelite_core PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    CXX_VISIBILITY_PRESET hidden
)

get_target_property(VISIBILITY imagelite_core CXX_VISIBILITY_PRESET)
message("Visibility for imagelite_core: ${VISIBILITY}")

target_compile_definitions(imagelite_core PRIVATE
    $<$<CONFIG:Debug>:IMAGELITE_DEBUG>
    $<$<CONFIG:Release>:IMAGELITE_RELEASE>
)
