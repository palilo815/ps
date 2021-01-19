#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;

struct _query {
    int i, j, limit;
};

int h[mxN], kid[mxN], lo[mxN + 1], hi[mxN];
_query query[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k, q;
    cin >> n >> m >> k >> q;

    for (int i = 0; i < m; ++i)
        cin >> h[i];
    for (int i = 0; i < k; ++i)
        cin >> kid[i], --kid[i];
    for (int i = 0; i < q; ++i) {
        cin >> query[i].i >> query[i].j >> query[i].limit;
        --query[i].i, --query[i].j, query[i].limit = h[query[i].limit - 1];
    }

    fill(hi, hi + q, k);

    for (;;) {
        vector<vector<int>> check(k);
        bool done = true;
        for (int i = 0; i < q; ++i)
            if (lo[i] != hi[i]) {
                check[(lo[i] + hi[i]) >> 1].emplace_back(i);
                done = false;
            }
        if (done) break;

        memset(h, 0, sizeof(int) * n);

        for (int m = 0; m < k; ++m) {
            ++h[kid[m]];
            for (int& i : check[m])
                h[query[i].i] + h[query[i].j] >= query[i].limit ? hi[i] = m : lo[i] = m + 1;
        }
    }

    sort(lo, lo + q);
    lo[q] = INT_MAX;

    for (int i = 0, j = 0; i < k; ++i) {
        // lo[q] is sentinel
        while (i == lo[j]) ++j;
        cout << j << '\n';
    }
}