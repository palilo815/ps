#include <bits/stdc++.h>
using namespace std;
struct elem {
    int x, idx;
};

const int mxN = 1e3;

elem a[mxN * mxN];
int cnt[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N * M; ++i)
        cin >> a[i].x;
    for (int i = 0; i < N; ++i)
        for (int j = i * M; j < (i + 1) * M; ++j)
            a[j].idx = i;

    sort(a, a + N * M, [&](auto& a, auto& b) {
        return a.x < b.x;
    });

    int ans = INT_MAX;
    for (int i = 0, j = 0, s = 0;;) {
        if (s == N) {
            ans = min(ans, a[j - 1].x - a[i].x);
            s -= --cnt[a[i++].idx] == 0;
        } else {
            if (j == N * M) break;
            s += ++cnt[a[j++].idx] == 1;
        }
    }
    cout << ans;
    return 0;
}