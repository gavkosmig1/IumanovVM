set(TARGET "calculator")
project(${TARGET} LANGUAGES CXX)
add_executable(
    ${TARGET}
    aboba.cpp
)
install(TARGETS ${TARGET})