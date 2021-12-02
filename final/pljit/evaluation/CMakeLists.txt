set(EVAL_SOURCES
    SymbolTable.cpp
    EvaluationContext.cpp
    OptimizationTable.cpp
    )

add_library(evaluation_core ${EVAL_SOURCES})
target_include_directories(evaluation_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_evaluation_core ${AST_SOURCES})
add_dependencies(lint lint_evaluation_core)

target_link_libraries(evaluation_core PUBLIC codem_core)
