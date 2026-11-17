cmake_minimum_required(VERSION 3.15)
project(main CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Strictly require system yaml-cpp. If apt package isn't found, CMake will error out 
# immediately instead of falling back to downloading code.
find_package(yaml-cpp REQUIRED)

file(GLOB_RECURSE SRCS
    "./src/*.cpp"
)

add_executable(main ${SRCS})
target_link_libraries(main PRIVATE yaml-cpp::yaml-cpp)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)