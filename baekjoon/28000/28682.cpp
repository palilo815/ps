#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    constexpr auto N = 1500;
    int _;
    cin >> _;
    for (auto i = 0; i < N; ++i) {
        cout << "soccer ";
    }
    cout << endl;
    array<bool, N> check;
    char buf[9];
    for (auto &x : check) {
        cin >> buf;
        x = (buf[0] == 's');
    }
    for (const auto &x : check) {
        cout << (x ? "bowling " : "swimming ");
    }
    cout << endl;
}
