set(AST_SOURCES
    ASTPrintVisitor.cpp
    AST.cpp
    ASTOptimizerDeadCode.cpp
    ASTOptimizerConstantPropagation.cpp
    )

add_library(ast_core ${AST_SOURCES})
target_include_directories(ast_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_ast_core ${AST_SOURCES})
add_dependencies(lint lint_ast_core)

target_link_libraries(ast_core PUBLIC evaluation_core)
#target_link_libraries(ast_core PUBLIC parser_core)
