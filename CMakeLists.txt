cmake_minimum_required(VERSION 3.15)
project(main CXX) #TODO cambiar el nombre de proyecto

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
  GIT_TAG 0.8.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_MakeAvailable(yaml-cpp)

# 2. Gather C++ source files
file(GLOB_RECURSE SRCS  # TODO cambiar a los .cpp tal cual no a todos
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

