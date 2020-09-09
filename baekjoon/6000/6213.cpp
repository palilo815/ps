#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;

const int sgN = 65536;

int minT[sgN << 1], maxT[sgN << 1];

int query(int l, int r) {
    int mn = INT_MAX, mx = INT_MIN;
    for (l += sgN, r += sgN; l ^ r; l >>= 1, r >>= 1) {
        if (l & 1) {
            mn = min(mn, minT[l]), mx = max(mx, maxT[l]);
            ++l;
        }
        if (r & 1) {
            --r;
            mn = min(mn, minT[r]), mx = max(mx, maxT[r]);
        }
    }
    return mx - mn;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    for (int i = sgN; i < sgN + N; ++i)
        cin >> minT[i];

    copy(minT + sgN, minT + sgN + N, maxT + sgN);
    for (int i = sgN - 1; i; --i) {
        minT[i] = min(minT[left], minT[right]);
        maxT[i] = max(maxT[left], maxT[right]);
    }

    for (int u, v; Q--;) {
        cin >> u >> v;
        cout << query(--u, v) << '\n';
    }
    return 0;
}