#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
int M;

struct elem {
    int d, h, idx;
    elem(int d = -1, int h = -1, int idx = -1) : d(d), h(h), idx(idx) {}
    bool operator<(const elem& rhs) const {
        if (d ^ rhs.d) return d < rhs.d;
        if (h ^ rhs.h) return h < rhs.h;
        return idx % M > rhs.idx % M;
    }
};

elem a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i].d >> a[i].h;

    priority_queue<elem> pq;
    for (int i = 0; i < M; ++i)
        pq.emplace(a[i].d, a[i].h, i);

    int ans = 0;
    for (;; ++ans) {
        int i = pq.top().idx;
        pq.pop();
        if (i == K) break;

        if (i + M < N) pq.emplace(a[i + M].d, a[i + M].h, i + M);
    }
    cout << ans;
    return 0;
}