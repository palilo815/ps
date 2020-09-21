#include <bits/stdc++.h>
using namespace std;
struct elem {
    int s, t;
    elem(int s, int t) : s(s), t(t) {}
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    vector<elem> vt;
    int ans = 0;
    for (int i = 0, q, s, t; i < N; ++i) {
        cin >> q;
        if (q) {
            cin >> s >> t;
            vt.emplace_back(s, t);
        }
        if (!vt.empty() && --vt.back().t == 0) {
            ans += vt.back().s;
            vt.pop_back();
        }
    }
    cout << ans;
    return 0;
}