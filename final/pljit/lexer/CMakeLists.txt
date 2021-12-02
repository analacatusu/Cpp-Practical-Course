set(LEXER_SOURCES
    Lexer.cpp
    )

add_library(lexer_core ${LEXER_SOURCES})
target_include_directories(lexer_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_lexer_core ${LEXER_SOURCES})
add_dependencies(lint lint_lexer_core)

target_link_libraries(lexer_core PUBLIC codem_core)
