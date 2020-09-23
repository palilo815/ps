#include <bits/stdc++.h>
using namespace std;
struct elem {
    int h, k;
};

const int mxN = 5e5;

elem a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].h >> a[i].k;

    sort(a, a + N, [&](auto& a, auto& b) {
        return a.h > b.h;
    });

    vector<int> vt;
    for (int i = 0; i < N; ++i) {
        auto it = upper_bound(vt.begin(), vt.end(), a[i].k, [&](auto& a, auto& b) { return a > b; });
        it == vt.end() ? vt.emplace_back(1) : ++*it;
    }
    cout << vt.size();
    return 0;
}