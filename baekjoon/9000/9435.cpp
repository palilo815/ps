#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

int N, Q;
p segT[max_N * 2];

void init() {
    cin >> N >> Q;
    for (int i = 0; i < N; ++i)
        segT[i + N] = { i,i };
    for (int i = N - 1; i; --i)
        segT[i].first = min(segT[i << 1].first, segT[i << 1 | 1].first),
        segT[i].second = max(segT[i << 1].second, segT[i << 1 | 1].second);
}
void update(int i) {
    while (i > 1) {
        segT[i >> 1].first = min(segT[i].first, segT[i ^ 1].first);
        segT[i >> 1].second = max(segT[i].second, segT[i ^ 1].second);
        i >>= 1;
    }
}
p query(int l, int r) {
    p ret = { INT_MAX,INT_MIN };
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            ret.first = min(ret.first, segT[l].first);
            ret.second = max(ret.second, segT[l].second);
            ++l;
        }
        if (r & 1) {
            --r;
            ret.first = min(ret.first, segT[r].first);
            ret.second = max(ret.second, segT[r].second);
        }
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
start:;
    init();
    while (Q--) {
        int q, l, r; cin >> q >> l >> r;
        if (q) {
            p res = query(l, r + 1);
            cout << (res.first == l && res.second == r ? "YES" : "NO") << '\n';
        }
        else {
            swap(segT[l + N], segT[r + N]);
            update(l + N), update(r + N);
        }
    }
    if (--T) goto start;
    return 0;
}