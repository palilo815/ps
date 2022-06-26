#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    array<int, 4> suit {};
    array<int, 10> num {};
    for (auto i {5}; i--;) {
        char s;
        int n;
        cin >> s >> n;
        if (s == 'R') ++suit[0];
        if (s == 'B') ++suit[1];
        if (s == 'Y') ++suit[2];
        if (s == 'G') ++suit[3];
        ++num[n];
    }
    const auto same_suit {find(suit.begin(), suit.end(), 5) != suit.end()};
    const auto conti_num {[&]() {
        const auto it {find(num.begin(), num.end(), 1)};
        return it + 4 < num.end() && *(it + 1) == 1 && *(it + 2) == 1 && *(it + 3) == 1 && *(it + 4) == 1;
    }()};
    const auto max_num {9 - (find_if(num.rbegin(), num.rend(), [&](const auto& x) {
        return x;
    }) - num.rbegin())};
    if (same_suit && conti_num) {
        cout << 900 + max_num;
    } else if (auto it {find(num.begin(), num.end(), 4)};
               it != num.end()) {
        cout << 800 + (it - num.begin());
    } else if (auto [it, jt] {pair(find(num.begin(), num.end(), 3), find(num.begin(), num.end(), 2))};
               it != num.end() && jt != num.end()) {
        cout << 700 + 10 * (it - num.begin()) + (jt - num.begin());
    } else if (same_suit) {
        cout << 600 + max_num;
    } else if (conti_num) {
        cout << 500 + max_num;
    } else if (auto it {find(num.begin(), num.end(), 3)};
               it != num.end()) {
        cout << 400 + (it - num.begin());
    } else if (count(num.begin(), num.end(), 2) == 2) {
        auto it {find(num.begin(), num.end(), 2)};
        auto jt {find(next(it), num.end(), 2)};
        cout << 300 + 10 * (jt - num.begin()) + (it - num.begin());
    } else if (auto it {find(num.begin(), num.end(), 2)};
               it != num.end()) {
        cout << 200 + (it - num.begin());
    } else {
        cout << 100 + max_num;
    }
}
