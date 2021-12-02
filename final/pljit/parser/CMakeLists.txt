set(PARSER_SOURCES
    Parser.cpp
    )

add_library(parser_core ${PARSER_SOURCES})
target_include_directories(parser_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_parser_core ${PARSER_SOURCES})
add_dependencies(lint lint_parser_core)

target_link_libraries(parser_core PUBLIC parsetree_core)
target_link_libraries(parser_core PUBLIC lexer_core)
