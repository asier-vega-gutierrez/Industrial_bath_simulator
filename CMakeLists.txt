cmake_minimum_required(VERSION 3.15)
project(main CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compiler warnings (-Wall -Wextra)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# 1. Fetch and configure yaml-cpp automatically
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "Disable yaml-cpp tests" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "Disable yaml-cpp tools" FORCE)
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "Disable yaml-cpp contrib" FORCE)
include(FetchContent)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.9.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)

# yaml-cpp 0.9.0 assumes the standard integer typedefs are available in
# emitterutils.cpp. GCC 15 is stricter and requires <cstdint> to be included
# before the uint16_t/uint32_t typedefs are used. Patch the downloaded source
# before the target is created so the dependency builds correctly on newer toolchains.
FetchContent_GetProperties(yaml-cpp)
if(NOT yaml-cpp_POPULATED)
    FetchContent_Populate(yaml-cpp)
endif()

set(EMITTER_UTILS_FILE "${yaml-cpp_SOURCE_DIR}/src/emitterutils.cpp")
if(EXISTS "${EMITTER_UTILS_FILE}")
    file(READ "${EMITTER_UTILS_FILE}" EMITTER_CONTENT)
    if(NOT EMITTER_CONTENT MATCHES "#include <cstdint>")
        string(PREPEND EMITTER_CONTENT "#include <cstdint>\n")
        file(WRITE "${EMITTER_UTILS_FILE}" "${EMITTER_CONTENT}")
        message(STATUS "Patched yaml-cpp emitterutils.cpp with #include <cstdint>")
    endif()
endif()

add_subdirectory("${yaml-cpp_SOURCE_DIR}" "${yaml-cpp_BINARY_DIR}")

# 2. Gather C++ source files
file(GLOB_RECURSE SRCS
    "./src/*.cpp"
)

# 3. Create executable target
add_executable(main ${SRCS})

# 4. Link yaml-cpp library target
target_link_libraries(main PRIVATE yaml-cpp::yaml-cpp)

# 5. Output binary to ../bin directory
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

