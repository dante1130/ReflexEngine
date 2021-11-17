# Minimum CMake version
cmake_minimum_required (VERSION 3.8)

# Project declaration.
project (ReflexEngine)

# CMake files for finding libraries.
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory(${CMAKE_PREFIX_PATH}/glm)
add_subdirectory(${CMAKE_PREFIX_PATH}/glad)

# Find the libraries using CMake modules.
find_package(SDL2 REQUIRED)

# Globs all the source files.
file (GLOB SOURCE_FILES src/*.cpp)

# Globs all the header files.
file (GLOB HEADER_FILES src/*.h)

# Globs all the DLLS.
file (GLOB DLLS ${CMAKE_PREFIX_PATH}/lib/x86/*.dll)

# Copies the DLL to build path.
file (COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Adds the source and header files to build.
add_executable (ReflexEngine ${HEADER_FILES} ${SOURCE_FILES})

# Include dependencies.
include_directories (ReflexEngine PUBLIC ${SDL2_INCLUDE_DIRS})
include_directories (ReflexEngine PUBLIC ${CMAKE_PREFIX_PATH}/glad/include)

# Link libraries.
target_link_libraries (ReflexEngine ${SDL2_LIBRARIES})
target_link_libraries (ReflexEngine glm)
target_link_libraries (ReflexEngine glad)