set(TARGET "calculator")
project(${TARGET} LANGUAGES CXX)
add_executable(
    ${TARGET}
    calculator.cpp
    functions.cpp
    grammar.cpp
    token.cpp
    variable.cpp
)
install(TARGETS ${TARGET})