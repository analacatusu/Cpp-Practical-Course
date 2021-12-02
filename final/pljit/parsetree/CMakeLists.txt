set(PT_SOURCES
    ParseTree.cpp
    ParseTreePrintVisitor.cpp
    )

add_library(parsetree_core ${PT_SOURCES})
target_include_directories(parsetree_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_parsetree_core ${PT_SOURCES})
add_dependencies(lint lint_parsetree_core)

target_link_libraries(parsetree_core PUBLIC codem_core)
