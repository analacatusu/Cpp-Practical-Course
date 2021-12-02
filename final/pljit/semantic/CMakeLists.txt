set(SEMANTIC_SOURCES
    SemanticAnalysis.cpp
    )

add_library(semantic_core ${SEMANTIC_SOURCES})
target_include_directories(semantic_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_semantic_core ${SEMANTIC_SOURCES})
add_dependencies(lint lint_semantic_core)

target_link_libraries(semantic_core PUBLIC ast_core)
target_link_libraries(semantic_core PUBLIC parser_core)
