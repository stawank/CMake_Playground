include(FetchContent)

FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master  # Or a specific commit for stability
)

FetchContent_MakeAvailable(stb)

# Create an interface library for the header-only STB library
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})

add_imagelite_module(imagelite_core
    src/core.cpp
    src/image.cpp
    src/platform_info.cpp
)

# imagelite_core must exist before we try to link libraries to it
target_link_libraries(imagelite_core PRIVATE stb_image)

set_target_properties(imagelite_core PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    CXX_VISIBILITY_PRESET hidden
)

get_target_property(VISIBILITY imagelite_core CXX_VISIBILITY_PRESET)
message("Visibility for imagelite_core: ${VISIBILITY}")

target_compile_definitions(imagelite_core PRIVATE
    $<$<CONFIG:Debug>:IMAGELITE_DEBUG>
    $<$<CONFIG:Debug>:IMAGELITE_ENABLE_LOGGING>
    $<$<CONFIG:Release>:IMAGELITE_RELEASE>
)

# Set platform-specific definitions
if(WIN32)
    target_compile_definitions(imagelite_core PUBLIC IL_PLATFORM_WINDOWS=1)
    target_compile_definitions(imagelite_core PUBLIC IL_PLATFORM_NAME="Windows")
elseif(APPLE)
    target_compile_definitions(imagelite_core PUBLIC IL_PLATFORM_MACOS=1)
    target_compile_definitions(imagelite_core PUBLIC IL_PLATFORM_NAME="macOS")
elseif(UNIX)
    target_compile_definitions(imagelite_core PUBLIC IL_PLATFORM_LINUX=1)
    target_compile_definitions(imagelite_core PUBLIC IL_PLATFORM_NAME="Linux")
else()
    target_compile_definitions(imagelite_core PUBLIC IL_PLATFORM_UNKNOWN=1)
    target_compile_definitions(imagelite_core PUBLIC IL_PLATFORM_NAME="Unknown")
endif()