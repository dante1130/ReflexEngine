# Minimum CMake version
cmake_minimum_required (VERSION 3.17)

# Project declaration.
project (ReflexEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# CMake path for libraries.
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Set to not build docs, tests and examples of GLFW.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RP3D_COMPILE_TESTBED OFF CACHE BOOL "" FORCE)
set(RP3D_COMPILE_TEST OFF CACHE BOOL "" FORCE)
set(RP3D_PROFILING_ENABLED OFF CACHE BOOL "" FORCE)
set(RP3D_DOUBLE_PRECISION_ENABLED OFF CACHE BOOL "" FORCE)

add_executable (ReflexEngine)

# Add subdirectories.
add_subdirectory(${CMAKE_PREFIX_PATH}/glm)
add_subdirectory(${CMAKE_PREFIX_PATH}/glad)
add_subdirectory(${CMAKE_PREFIX_PATH}/glfw)
add_subdirectory(${CMAKE_PREFIX_PATH}/imgui)
add_subdirectory(${CMAKE_PREFIX_PATH}/lua)
add_subdirectory(${CMAKE_PREFIX_PATH}/reactphysics3d)
add_subdirectory(${CMAKE_PREFIX_PATH}/raknet)

add_subdirectory(src)


target_compile_options(${PROJECT_NAME} PRIVATE
    # Clang
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Weverything -fcolor-diagnostics
        # Turn off useless warnings
        -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
        -Wno-deprecated-declarations -Wno-exit-time-destructors
        -Wno-switch-enum -Wno-weak-vtables -Wno-global-constructors>
    # GCC
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
    # Visual Studio
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_custom_command(TARGET ReflexEngine POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${PROJECT_SOURCE_DIR}/dlls 
                    ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET ReflexEngine POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${PROJECT_SOURCE_DIR}/resources 
                    ${CMAKE_CURRENT_BINARY_DIR})

# Include dependencies.
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glad/include)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glfw/include)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glm)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/stb_image)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/assimp/include)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/imgui)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/reactphysics3d)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/raknet/include)

# Link libraries.
target_link_libraries (ReflexEngine PRIVATE glfw)
target_link_libraries (ReflexEngine PRIVATE glm)
target_link_libraries (ReflexEngine PRIVATE glad)
target_link_libraries (ReflexEngine PRIVATE ${CMAKE_PREFIX_PATH}/assimp/lib/assimp-vc143-mt.lib)
target_link_libraries (ReflexEngine PRIVATE imgui)
target_link_libraries (ReflexEngine PRIVATE lua)
target_link_libraries (ReflexEngine PRIVATE reactphysics3d)
target_link_libraries (ReflexEngine PRIVATE ${CMAKE_PREFIX_PATH}/raknet/Lib/DLL_vc9_DLL_Release_x64.lib)
target_link_libraries (ReflexEngine PRIVATE ${CMAKE_PREFIX_PATH}/raknet/Lib/LibStatic_vc9_LibStatic_Release_x64.lib)