#include "hat.h"
#include <bits/stdc++.h>
using namespace std;

void init(int n) {
    // Do Something...
}

int call(vector<int> f, vector<int> b, int num) {
    if (num + 1 == f.size()) {
        return accumulate(f.begin(), f.end(), 0, [&](const auto& sum, const auto& x) {
            return sum ^ x;
        });
    } else {
        return accumulate(f.begin(), f.begin() + num, 0, [&](const auto& sum, const auto& x) {
            return sum ^ x;
        }) ^ accumulate(b.begin() + num, b.end(), 0, [&](const auto& sum, const auto& x) {
            return sum ^ x;
        });
    }
}