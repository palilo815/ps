#include <bits/stdc++.h>
using namespace std;

const int mxN = 3e5;

pair<int, int> a[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> a[i].first;

    vector<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && a[stk.back()].first >= a[i].first)
            stk.pop_back();
        if (!stk.empty()) a[i].second = ~stk.back();
        stk.emplace_back(i);
    }
    stk.clear();
    for (int i = n - 1; ~i; --i) {
        while (!stk.empty() && a[stk.back()].first >= a[i].first)
            stk.pop_back();
        a[i].second += stk.empty() ? n : stk.back();
        stk.emplace_back(i);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans = max(ans, min(a[i].first, a[i].second));
    cout << ans;
}