#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

int arr[max_N];
p segT[131072 * 2 - 1];

inline p min_max(p a, p b) {
    return { min(a.first,b.first),max(a.second,b.second) };
}
p build_segT(int l, int r, int idx) {
    if (l == r) return segT[idx] = { arr[l],arr[l] };
    int m = l + (r - l) / 2;
    int c1 = 2 * idx + 1, c2 = 2 * idx + 2;
    build_segT(l, m, c1);
    build_segT(m + 1, r, c2);
    return segT[idx] = min_max(segT[c1], segT[c2]);
}
p query(int ql, int qr, int l, int r, int idx) {
    if (ql <= l && r <= qr) return segT[idx];
    if (qr < l || r < ql) return { INT_MAX,INT_MIN };
    int m = l + (r - l) / 2;
    int c1 = 2 * idx + 1, c2 = 2 * idx + 2;
    return min_max(query(ql, qr, l, m, c1), query(ql, qr, m + 1, r, c2));
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    build_segT(0, N - 1, 0);

    while (M--) {
        int ql, qr; cin >> ql >> qr;
        p ans = query(ql - 1, qr - 1, 0, N - 1, 0);
        cout << ans.first << ' ' << ans.second << '\n';
    }
    return 0;
}