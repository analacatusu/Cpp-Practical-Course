set(TEST_SOURCES
#add your source files here
    TestLexer.cpp
    TestParser.cpp
    TestAST.cpp
    TestEvaluation.cpp
    TestOptimization.cpp
    TestPljit.cpp
    TestASTPrintVisitor.cpp
    TestParseTreePrintVisitor.cpp
    Tester.cpp
    )

add_executable(tester ${TEST_SOURCES})
target_link_libraries(tester PUBLIC
                      pljit_core
                      GTest::GTest)
