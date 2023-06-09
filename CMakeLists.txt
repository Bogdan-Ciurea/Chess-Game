# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.16.3)

project(api_server VERSION 0.1.0 LANGUAGES CXX)


# Set a default C++ compile flag
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Set the project name
project(chess)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES 
    src/main.cpp
    src/pieces.cpp
    src/functions.cpp
    src/chess_board.cpp
    src/cell.cpp
    src/cell_position.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Libraries
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/raylib)
include_directories(${PROJECT_SOURCE_DIR}/modules/raylib/src)


target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src/extras)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)