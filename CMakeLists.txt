cmake_minimum_required(VERSION 3.31.3)

# Project name and version
project(3d-renderer VERSION 1.0 LANGUAGES CXX)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories for builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Automatically gather all source and header files
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/include/*.cpp"
)

# Define the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

if (MSVC)
    # Microsoft compiler
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    # GCC, Clang, etc.
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

# Build-type-specific flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug build mode")
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g>)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release build mode")
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O3>)
endif()