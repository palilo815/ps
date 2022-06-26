#include "cave.h"
#include <bits/stdc++.h>

void exploreCave(int n) {
    using namespace std;
    vector<int> s(n), d(n, -1), unknown(n);
    iota(unknown.begin(), unknown.end(), 0);
    auto solve = [&](int door_id) {
        const auto res_if_0 {tryCombination(s.data()) == door_id};
        int lo {}, hi {static_cast<int>(unknown.size()) - 1};
        while (lo != hi) {
            const auto mid {(lo + hi) >> 1};
            for (int i = lo; i <= mid; ++i) {
                s[unknown[i]] = 1;
            }
            const auto res {tryCombination(s.data()) == door_id};
            for (int i = lo; i <= mid; ++i) {
                s[unknown[i]] = 0;
            }
            res == res_if_0 ? lo = mid + 1 : hi = mid;
        }
        s[unknown[lo]] = res_if_0;
        d[unknown[lo]] = door_id;
        unknown.erase(unknown.begin() + lo);
    };
    for (int i = 0; i < n; ++i) {
        solve(i);
    }
    answer(s.data(), d.data());
}
