cmake_minimum_required(VERSION 3.15)
project(main CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compiler warnings (-Wall -Wextra)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Find system-installed yaml-cpp package
find_package(yaml-cpp REQUIRED)

# Gather C++ source files
file(GLOB_RECURSE SRCS
    "./src/*.cpp"
)

# Create executable target
add_executable(main ${SRCS})

# Link yaml-cpp library target
target_link_libraries(main PRIVATE yaml-cpp::yaml-cpp)

# Output binary to ../bin directory
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)