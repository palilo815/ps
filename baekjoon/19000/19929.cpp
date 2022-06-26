#include "gift.h"
#include <bits/stdc++.h>

int construct(int n, int r, std::vector<int> a, std::vector<int> b, std::vector<int> x) {
    using namespace std;
    vector<int> cnt_begin(n), cnt_end(n);
    for (int i = 0; i < r; ++i) {
        if (x[i] == 1) {
            ++cnt_begin[a[i]];
            ++cnt_end[b[i]];
        }
    }
    int id = 0;
    auto& colour = cnt_begin;
    for (int i = 0, psum = 0; i < n; ++i) {
        psum += cnt_begin[i];
        colour[i] = id;
        psum -= cnt_end[i];
        if (psum == 0) ++id;
    }
    for (int i = 0; i < r; ++i) {
        if (x[i] == 2 && colour[a[i]] == colour[b[i]]) {
            return 0;
        }
    }
    string s(n, 0);
    transform(colour.begin(), colour.end(), s.begin(), [&](const auto& x) {
        return x & 1 ? 'R' : 'B';
    });
    craft(s);
    return 1;
}
