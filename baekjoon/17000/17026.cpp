#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;

const int mxN = 1e5;

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
        cin >> a[i].x >> a[i].y;

    sort(a, a + n, [&](auto& a, auto& b) {
        return a.x < b.x;
    });

    vector<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && a[i].x - a[stk.back()].x <= a[i].y - a[stk.back()].y)
            stk.pop_back();
        if (stk.empty() || a[i].x - a[stk.back()].x > a[stk.back()].y - a[i].y)
            stk.emplace_back(i);
    }
    cout << stk.size();
}