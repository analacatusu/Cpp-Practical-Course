#include "pljit/Pljit.hpp"
using namespace std;
using namespace pljit;

int main() {
    Pljit jit;

    auto func1 = jit.registerFunction("PARAM a, b; VAR d; CONST c = 2; BEGIN d := (a + b); d := d * c; RETURN d END.");
    auto func2 = jit.registerFunction("VAR d, e; BEGIN d := -1 * (12 / (-6)); e := d + +2; e := -(-(-e)); RETURN e; RETURN d END.");
    auto func3 = jit.registerFunction("PARAM a; VAR b; CONST c = 1; BEGIN b := a - c - 2; RETURN b END.");

    vector<int64_t> params1 = {1, 2};
    vector<int64_t> params2;
    vector<int64_t> params3 = {4};

    auto res1 = func1(params1);

    if (res1.has_value()) {
        cout << "result func1 = " << res1.value() << endl;
    }

    auto res2 = func2(params2);

    if (res2.has_value()) {
        cout << "result func2 = " << res2.value() << endl;
    }

    auto res3 = func3(params3);

    if (res3.has_value()) {
        cout << "result func3 = " << res3.value() << endl;
    }
}
