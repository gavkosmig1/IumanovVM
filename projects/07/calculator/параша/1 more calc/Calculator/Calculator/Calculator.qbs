import qbs

CppApplication {
    consoleApplication: true
    files: [
        "calculator.cpp",
        "token.cpp",
        "variable.cpp",
        "token.h",
        "variable.h"
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
