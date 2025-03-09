# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h" "Token.h" "Token.cpp" "Token_stream.h" "Token_stream.cpp"  "Const.h" "Variable.h" "Variable.cpp" "Variables.cpp" "Variables.h" "Calculate.h" "Calculate.cpp" "RomanNumsConvert.cpp" "RomanNumsConvert.h" "CanRoman.cpp" "RomanToDec.cpp" "DecToRoman.cpp" "RomanNumbers.h")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
