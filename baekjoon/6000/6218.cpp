#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 50000;

int arr[max_N];
p segT[65536 * 2 - 1];

void init_segT(int l, int r, int i) {
    if (l == r) {
        segT[i] = { arr[l],arr[l] };
        return;
    }
    int m = (l + r) / 2;
    init_segT(l, m, 2 * i + 1);
    init_segT(m + 1, r, 2 * i + 2);
    segT[i].first = min(segT[2 * i + 1].first, segT[2 * i + 2].first);
    segT[i].second = max(segT[2 * i + 1].second, segT[2 * i + 2].second);
}
p query(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) return segT[i];
    if (qr < l || r < ql) return { INT_MAX,INT_MIN };
    int m = (l + r) / 2;
    p L = query(ql, qr, l, m, 2 * i + 1);
    p R = query(ql, qr, m + 1, r, 2 * i + 2);
    return { min(L.first,R.first),max(L.second,R.second) };
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    for (int i = 1; i <= N; ++i)
        cin >> arr[i];

    init_segT(1, N, 0);

    while (Q--) {
        int ql, qr; cin >> ql >> qr;
        p res = query(ql, qr, 1, N, 0);
        cout << res.second - res.first << '\n';
    }
    return 0;
}