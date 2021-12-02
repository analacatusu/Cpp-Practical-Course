set(CODEM_SOURCES
    CodeManagement.cpp
    Reference.cpp
    )

add_library(codem_core ${CODEM_SOURCES})
target_include_directories(codem_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_codem_core ${CODEM_SOURCES})
add_dependencies(lint lint_codem_core)
