#include <bits/stdc++.h> 
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

int N;
p segT[max_N * 2];

p max_2(p& a, p& b) {
    p ret = { 0,0 };
    ret.first = max(a.first, b.first);
    ret.second = max(min(a.first, b.first), max(a.second, b.second));
    return ret;
}
void update(int p, int v) {
    segT[p + N].first = v;
    for (int i = p + N; i > 1; i /= 2)
        segT[i / 2] = max_2(segT[i], segT[i ^ 1]);
}
int query(int l, int r) {
    p res = { 0,0 };
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
        if (l & 1) res = max_2(res, segT[l++]);
        if (r & 1) res = max_2(res, segT[--r]);
    }
    return res.first + res.second;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    for (int i = N; i < 2 * N; ++i)
        cin >> segT[i].first;
    for (int i = N - 1; i; --i)
        segT[i] = max_2(segT[i * 2], segT[i * 2 | 1]);

    int Q; cin >> Q;
    while (Q--) {
        int q, a, b; cin >> q >> a >> b;
        if (q == 1) update(a - 1, b);
        else cout << query(a - 1, b) << '\n';
    }
    return 0;
}