#include "pljit/Pljit.hpp"
#include <thread>
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
using namespace std;
using namespace pljit;
//---------------------------------------------------------------------------
TEST(TestPljit, MultipleFunctionsCorrect) {
    const auto program =
        "PARAM c;\n"
        "VAR d, e;\n"
        "CONST f = 10;\n"
        "BEGIN\n"
        "c := f - (-1);\n"
        "e := c + -1;\n"
        "d := 1;\n"
        "e := e - d + 4;\n"
        "RETURN e\n"
        "END.\n";

    Pljit jit;
    auto func = jit.registerFunction(program);
    vector<int64_t> parameters;
    parameters.push_back(2); // c
    auto result = func(parameters);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result, 5);

    const auto program2 =
        "PARAM a, b, c;\n"
        "VAR d, e;\n"
        "BEGIN\n" // 67
        "d := a * b / c;\n"
        "e := d - (-(-3) * 2);\n"
        "RETURN e\n"
        "END.\n";

    auto func2 = jit.registerFunction(program2);
    vector<int64_t> parameters2;
    parameters2.push_back(4); // a
    parameters2.push_back(3); // b
    parameters2.push_back(1); // c
    auto result2 = func2(parameters2);
    ASSERT_TRUE(result2.has_value());
    ASSERT_EQ(result2, 6);

    const auto program3 =
        "PARAM a, b;\n"
        "VAR d, e;\n"
        "CONST f = 1, g = 12;\n"
        "BEGIN\n"
        "d := -a + f;\n"
        "d := d + -(-(-1)) + g / 2 * 3;\n"
        "e := d - b;\n"
        "RETURN e;\n"
        "RETURN f\n"
        "END.\n";

    auto func3 = jit.registerFunction(program3);
    vector<int64_t> parameters3;
    parameters3.push_back(-1); // a
    parameters3.push_back(4); // b
    auto result3 = func3(parameters3);
    ASSERT_TRUE(result3.has_value());
    ASSERT_EQ(result3, -1);
}
//---------------------------------------------------------------------------
TEST(TestPljit, MultipleFunctionsWithErrors) {
    const auto program =
        "PARAM c;\n"
        "VAR c, e;\n"
        "BEGIN\n"
        "c := 1;\n"
        "e := c - -3;\n"
        "RETURN c\n"
        "END.\n";

    Pljit jit;
    auto func = jit.registerFunction(program);
    vector<int64_t> parameters;
    parameters.push_back(2); // c
    cerr << endl
         << "program1 :" << endl;
    auto result = func(parameters);
    ASSERT_FALSE(result.has_value());

    const auto program2 =
        "PARAM a;\n"
        "VAR d;\n"
        "BEGIN\n" // 67
        "d := a\n"
        "END.\n";

    auto func2 = jit.registerFunction(program2);
    vector<int64_t> parameters2;
    parameters2.push_back(4); // a
    cerr << endl
         << "program2 :" << endl;
    auto result2 = func2(parameters2);
    ASSERT_FALSE(result2.has_value());

    const auto program3 =
        "VAR e;\n"
        "BEGIN\n"
        "RETURN e\n"
        "END.\n";

    auto func3 = jit.registerFunction(program3);
    vector<int64_t> parameters3;
    cerr << endl
         << "program3 :" << endl;
    auto result3 = func3(parameters3);
    ASSERT_FALSE(result3.has_value());
}
//---------------------------------------------------------------------------
TEST(TestPljit, ParallelSingleHandle) {
    const auto code =
        "PARAM a;\n"
        "BEGIN\n"
        "a := a * 2;\n"
        "RETURN a\n"
        "END.\n";

    Pljit jit;
    auto func1 = jit.registerFunction(code);
    vector<int64_t> parameters1 = {0};
    vector<int64_t> parameters2 = {1};
    vector<int64_t> parameters3 = {2};
    vector<int64_t> parameters4 = {3};
    vector<int64_t> parameters5 = {4};
    vector<int64_t> parameters6 = {5};
    vector<int64_t> parameters7 = {6};
    vector<int64_t> parameters8 = {7};
    vector<int64_t> parameters9 = {8};
    vector<int64_t> parameters10 = {9};

    vector<thread> threads;

    threads.emplace_back([&func1, &parameters1]() {
        auto res = func1(parameters1);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 0);
    });

    threads.emplace_back([&func1, &parameters2]() {
        auto res = func1(parameters2);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 2);
    });

    threads.emplace_back([&func1, &parameters3]() {
        auto res = func1(parameters3);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 4);
    });

    threads.emplace_back([&func1, &parameters4]() {
        auto res = func1(parameters4);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 6);
    });

    threads.emplace_back([&func1, &parameters5]() {
        auto res = func1(parameters5);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 8);
    });

    threads.emplace_back([&func1, &parameters6]() {
        auto res = func1(parameters6);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 10);
    });

    threads.emplace_back([&func1, &parameters7]() {
        auto res = func1(parameters7);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 12);
    });

    threads.emplace_back([&func1, &parameters8]() {
        auto res = func1(parameters8);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 14);
    });

    threads.emplace_back([&func1, &parameters9]() {
        auto res = func1(parameters9);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 16);
    });

    threads.emplace_back([&func1, &parameters10]() {
        auto res = func1(parameters10);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 18);
    });

    for (auto& thread : threads)
        thread.join();
}
//---------------------------------------------------------------------------
TEST(TestPljit, ParallelMultipleHandles) {
    const auto code1 =
        "PARAM a, b;\n"
        "BEGIN\n"
        "a := a + b;\n"
        "RETURN a\n"
        "END.\n";

    Pljit jit;
    auto func1 = jit.registerFunction(code1);
    auto func2 = jit.registerFunction(code1);
    auto func3 = jit.registerFunction(code1);

    vector<int64_t> parameters1 = {0, 1};
    vector<int64_t> parameters2 = {1, 2};
    vector<int64_t> parameters3 = {2, 3};
    vector<int64_t> parameters4 = {3, 4};
    vector<int64_t> parameters5 = {4, 5};
    vector<int64_t> parameters6 = {5, 6};
    vector<int64_t> parameters7 = {6, 7};
    vector<int64_t> parameters8 = {7, 8};
    vector<int64_t> parameters9 = {8, 9};
    vector<int64_t> parameters10 = {9, 10};

    auto res = func1(parameters1);
    ASSERT_TRUE(res.has_value());
    ASSERT_EQ(res, 1);
    ASSERT_TRUE(func1.isCompiled());
    auto res2 = func2(parameters2);
    ASSERT_TRUE(res2.has_value());
    ASSERT_EQ(res2, 3);
    ASSERT_TRUE(func2.isCompiled());
    ASSERT_FALSE(func3.isCompiled());

    vector<thread> threads;

    threads.emplace_back([&func1, &parameters1]() {
        auto res = func1(parameters1);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 1);
    });

    threads.emplace_back([&func1, &parameters2]() {
        auto res = func1(parameters2);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 3);
    });

    threads.emplace_back([&func1, &parameters3]() {
        auto res = func1(parameters3);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 5);
    });

    threads.emplace_back([&func2, &parameters4]() {
        auto res = func2(parameters4);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 7);
    });

    threads.emplace_back([&func2, &parameters5]() {
        auto res = func2(parameters5);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 9);
    });

    threads.emplace_back([&func2, &parameters6]() {
        auto res = func2(parameters6);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 11);
    });

    threads.emplace_back([&func3, &parameters7]() {
        auto res = func3(parameters7);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 13);
    });

    threads.emplace_back([&func3, &parameters8]() {
        auto res = func3(parameters8);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 15);
    });

    threads.emplace_back([&func3, &parameters9]() {
        auto res = func3(parameters9);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 17);
    });

    threads.emplace_back([&func3, &parameters10]() {
        auto res = func3(parameters10);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 19);
    });

    for (auto& thread : threads)
        thread.join();
}
//---------------------------------------------------------------------------
TEST(TestPljit, ParallelMultipleFunctions) {
    const auto code1 =
        "PARAM a, b;\n"
        "BEGIN\n"
        "a := a + b;\n"
        "RETURN a\n"
        "END.\n";

    const auto code2 =
        "PARAM c, d;\n"
        "BEGIN\n"
        "c := c + d + 1;\n"
        "RETURN c\n"
        "END.\n";

    Pljit jit;
    auto func1 = jit.registerFunction(code1);
    auto func2 = jit.registerFunction(code2);

    vector<int64_t> parameters1 = {0, 1};
    vector<int64_t> parameters2 = {1, 2};
    vector<int64_t> parameters3 = {2, 3};
    vector<int64_t> parameters4 = {3, 4};

    auto res = func1(parameters4);
    ASSERT_TRUE(res.has_value());
    ASSERT_EQ(res, 7);
    ASSERT_TRUE(func1.isCompiled());

    vector<thread> threads;

    threads.emplace_back([&func1, &parameters1]() {
        auto res = func1(parameters1);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 1);
    });

    threads.emplace_back([&func1, &parameters2]() {
        auto res = func1(parameters2);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 3);
    });

    threads.emplace_back([&func1, &parameters3]() {
        auto res = func1(parameters3);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 5);
    });

    threads.emplace_back([&func2, &parameters1]() {
        auto res = func2(parameters1);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 2);
    });

    threads.emplace_back([&func2, &parameters2]() {
        auto res = func2(parameters2);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 4);
    });

    threads.emplace_back([&func2, &parameters3]() {
        auto res = func2(parameters3);
        ASSERT_TRUE(res.has_value());
        ASSERT_EQ(res.value(), 6);
    });

    for (auto& thread : threads)
        thread.join();
}
//---------------------------------------------------------------------------
