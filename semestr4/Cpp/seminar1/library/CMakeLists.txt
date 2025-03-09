cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT shapelib)

set(SOURCES
    rectangle.cpp
    circle.cpp
    triangle.cpp
)

set(HEADERS 
    shape.h
    rectangle.h
    circle.h
    triangle.h
)

add_library(${PROJECT} SHARED ${SOURCES} ${HEADERS})