#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<double> r(n);
    for (auto& x : r) cin >> x;

    string s;
    cin >> s;

    stringstream sin(s);

    vector<vector<double>> r_stack(1); // R values
    vector<char> type_stack(1);        // series? parallel?

    auto series = [&](vector<double>& vt) -> double {
        return accumulate(vt.begin(), vt.end(), 0.0, [&](auto& sum, auto& x) {
            return sum + x;
        });
    };
    auto parallel = [&](vector<double>& vt) -> double {
        return 1.0 / accumulate(vt.begin(), vt.end(), 0.0, [&](auto& sum, auto& x) {
            return sum + 1.0 / x;
        });
    };

    for (char c; sin >> c;) {
        if (c == '(') {
            r_stack.emplace_back();
            type_stack.emplace_back();
        } else if (c == ')') {
            assert(type_stack.back());
            auto val = type_stack.back() == 's' ? series(r_stack.back()) : parallel(r_stack.back());
            type_stack.pop_back();
            r_stack.pop_back();
            r_stack.back().emplace_back(val);
        } else if (c == 'R') {
            int id;
            sin >> id, --id;
            r_stack.back().emplace_back(r[id]);
        } else {
            assert(c == '-' || c == '|');
            type_stack.back() = (c == '-' ? 's' : 'p');
        }
    }

    cout << fixed << setprecision(9);
    if (type_stack.back()) {
        assert(r_stack.back().size() > 1);
        cout << (type_stack.back() == 's' ? series(r_stack.back()) : parallel(r_stack.back()));
    } else {
        assert(r_stack.back().size() == 1);
        cout << r_stack.back().front();
    }
}