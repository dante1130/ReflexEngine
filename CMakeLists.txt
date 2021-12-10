# Minimum CMake version
cmake_minimum_required (VERSION 3.8)

# Project declaration.
project (ReflexEngine LANGUAGES CXX)

# Clang sanitizer settings.
set(SANITIZER_OS "Darwin,Linux")
set(SANITIZER_FLAGS "-fsanitize=address,undefined,leak")

# CMake files for finding libraries.
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory(${CMAKE_PREFIX_PATH}/glm)
add_subdirectory(${CMAKE_PREFIX_PATH}/glad)
add_subdirectory(${CMAKE_PREFIX_PATH}/glfw)

# Globs all the source files.
file (GLOB SOURCE_FILES src/*.cpp)

# Globs all the header files.
file (GLOB HEADER_FILES src/*.h)

# Adds the source and header files to build.
add_executable (ReflexEngine ${HEADER_FILES} ${SOURCE_FILES})

# Set compile flags.
target_compile_options(${PROJECT_NAME} PRIVATE
    # Clang
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Weverything -fcolor-diagnostics
        # Disable specific warnings.
        -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
        -Wno-deprecated-declarations -Wno-exit-time-destructors
        -Wno-switch-enum -Wno-weak-vtables -Wno-global-constructors>
    # GCC
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
    # Visual Studio
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    # Enable the clang sanitizer.
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
)
# Link against the clang sanitizer.
target_link_options(${PROJECT_NAME} PRIVATE
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
)

add_custom_command(TARGET ReflexEngine PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${PROJECT_SOURCE_DIR}/src/shaders 
                    ${CMAKE_CURRENT_BINARY_DIR}/shaders)

# Include dependencies.
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glad/include)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glfw/include)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glm)

# Link libraries.
target_link_libraries (ReflexEngine PRIVATE glfw)
target_link_libraries (ReflexEngine PRIVATE glm)
target_link_libraries (ReflexEngine PRIVATE glad)