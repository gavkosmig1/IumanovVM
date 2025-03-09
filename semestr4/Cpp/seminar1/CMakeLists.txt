cmake_minimum_required(VERSION 3.30)

set(PROJECT lib_example)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(library)

add_executable(${PROJECT} main.cpp)
target_link_libraries(${PROJECT} PRIVATE shapelib)
target_include_directories(${PROJECT} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/library)