add_subdirectory(codem)
add_subdirectory(lexer)
add_subdirectory(parsetree)
add_subdirectory(parser)
add_subdirectory(evaluation)
add_subdirectory(ast)
add_subdirectory(semantic)

set(PLJIT_SOURCES
    Pljit.cpp)

add_library(pljit_core ${PLJIT_SOURCES})
target_include_directories(pljit_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_pljit_core ${PLJIT_SOURCES})
add_dependencies(lint lint_pljit_core)

add_executable(pljit main.cpp)

target_link_libraries(pljit_core PUBLIC semantic_core)
target_link_libraries(pljit PUBLIC pljit_core)
