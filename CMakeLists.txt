# Minimum CMake version
cmake_minimum_required (VERSION 3.8)

# Project declaration.
project (ReflexEngine LANGUAGES CXX)

# CMake path for libraries.
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Set to not build docs, tests and examples of GLFW.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add subdirectories of libraries.
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
)

# Enable AddressSanitizer.
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# Copy shaders to build path.
add_custom_command(TARGET ReflexEngine PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${PROJECT_SOURCE_DIR}/src/shaders 
                    ${CMAKE_CURRENT_BINARY_DIR}/shaders)


add_custom_command(TARGET ReflexEngine PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${PROJECT_SOURCE_DIR}/src/textures 
                    ${CMAKE_CURRENT_BINARY_DIR}/textures)

# Include dependencies.
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glad/include)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glfw/include)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/glm)
include_directories (ReflexEngine SYSTEM ${CMAKE_PREFIX_PATH}/stb_image)

# Link libraries.
target_link_libraries (ReflexEngine PRIVATE glfw)
target_link_libraries (ReflexEngine PRIVATE glm)
target_link_libraries (ReflexEngine PRIVATE glad)

