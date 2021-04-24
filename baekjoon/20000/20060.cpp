#include "combo.h"
#include <bits/stdc++.h>
using namespace std;

string guess_sequence(int n) {
    string ans;
    ans.reserve(n);

    array a = {'A', 'B', 'X', 'Y'};

    auto guess_endpoint = [&]() {
        if (press(ans + a[0] + ans + a[1]) == int(ans.size()))
            ans += press(ans + a[2]) == int(ans.size()) ? a[3] : a[2];
        else
            ans += press(ans + a[0]) == int(ans.size()) ? a[1] : a[0];
    };
    auto guess_mid = [&]() {
        int matched = press(ans + a[0] + a[0] + ans + a[0] + a[1] + ans + a[0] + a[2] + ans + a[1]) - int(ans.size());
        if (matched == 0)
            ans += a[2];
        else if (matched == 1)
            ans += a[1];
        else
            ans += a[0];
    };

    // call `press` 2 + (n - 2) + 2

    // first
    guess_endpoint();
    if (n == 1) return ans;

    *find(a.begin(), a.end(), ans[0]) = 'Y';

    // n - 2
    for (int i = n - 2; i; --i)
        guess_mid();

    // last
    if (n != 1) guess_endpoint();
    return ans;
}