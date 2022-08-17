# Minimum CMake version
cmake_minimum_required(VERSION 3.17)

# Project declaration.
project(ReflexEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# CMake path for libraries.
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

enable_testing()

add_executable(ReflexEngine)
add_executable(ReflexEngineTest)

add_subdirectory(cmake)

add_subdirectory(src)
add_subdirectory(test)

target_compile_options(${PROJECT_NAME} PRIVATE

    # Clang
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
    -Wall -Wextra -Wpedantic -fcolor-diagnostics

    # Turn off useless warnings
    -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
    -Wno-deprecated-declarations -Wno-exit-time-destructors
    -Wno-switch-enum -Wno-weak-vtables -Wno-global-constructors>

    # GCC
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always -mbig-obj>

    # Visual Studio
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /bigobj>

    $<$<CONFIG:RELEASE>:-O3>
    $<$<CONFIG:DEBUG>:-O0>
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
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glad/include)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glfw/include)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glm)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/stb_image)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/assimp/include)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/imgui)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/reactphysics3d)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/irrklang)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/slikenet/Source)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/entt/single_include)
include_directories(ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/catch2/src)

# Link libraries.
target_link_libraries(ReflexEngine PRIVATE glfw)
target_link_libraries(ReflexEngine PRIVATE glm)
target_link_libraries(ReflexEngine PRIVATE glad)
target_link_libraries(ReflexEngine PRIVATE imgui)
target_link_libraries(ReflexEngine PRIVATE lua)
target_link_libraries(ReflexEngine PRIVATE reactphysics3d)
target_link_libraries(ReflexEngine PRIVATE EnTT)
target_link_libraries(ReflexEngine PRIVATE ${PROJECT_SOURCE_DIR}/lib/assimp-vc143-mt.lib)
target_link_libraries(ReflexEngine PRIVATE ${PROJECT_SOURCE_DIR}/lib/RakNet_DLL_Release_x64.lib)
target_link_libraries(ReflexEngine PRIVATE ${CMAKE_PREFIX_PATH}/irrklang/lib/irrKlang.lib)

target_link_libraries(ReflexEngineTest PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_PREFIX_PATH}/catch2/extras)

include(CTest)
include(Catch)
catch_discover_tests(ReflexEngineTest)
