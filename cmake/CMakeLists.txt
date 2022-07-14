cmake_minimum_required(VERSION 3.17)

function(target_ignore_warnings target scope)
    get_target_property(lib_include_dirs ${target} INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(${target} SYSTEM ${scope} ${lib_include_dirs})
endfunction()

# Set to not build docs, tests and examples
option(ASSIMP_BUILD_TESTS OFF)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_USE_HYBRID_HPG ON)
option(RP3D_COMPILE_TESTBED OFF)
option(RP3D_COMPILE_TEST OFF)
option(RP3D_PROFILING_ENABLED OFF)
option(RP3D_DOUBLE_PRECISION_ENABLED OFF)

# Disable compiler warnings.
add_compile_options(

    # Clang
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wno-everything>

    # GCC
    $<$<CXX_COMPILER_ID:GNU>:-w>

    # Visual Studio
    $<$<CXX_COMPILER_ID:MSVC>:/W0>
)

# Add subdirectories.
add_subdirectory(glm)
add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(imgui)
add_subdirectory(lua)
add_subdirectory(reactphysics3d)
add_subdirectory(entt)

target_ignore_warnings(glm INTERFACE)
target_ignore_warnings(glad INTERFACE)
target_ignore_warnings(glfw INTERFACE)
target_ignore_warnings(imgui INTERFACE)
target_ignore_warnings(lua INTERFACE)
target_ignore_warnings(reactphysics3d INTERFACE)
target_ignore_warnings(EnTT INTERFACE)
