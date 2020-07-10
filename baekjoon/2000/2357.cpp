#include<bits/stdc++.h>
using namespace std;

const int max_N = 1e5;

int N, M;
int minT[max_N << 1];
int maxT[max_N << 1];

pair<int, int> query(int l, int r) {
    int x = INT_MAX, y = INT_MIN;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            x = min(x, minT[l]), y = max(y, maxT[l]);
            ++l;
        }
        if (r & 1) {
            --r;
            x = min(x, minT[r]), y = max(y, maxT[r]);
        }
    }
    return {x, y};
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    for (int i = N; i < N << 1; ++i)
        cin >> minT[i];
    copy(minT + N, minT + N + N, maxT + N);

    for (int i = N - 1; i; --i) {
        minT[i] = min(minT[i << 1], minT[i << 1 | 1]);
        maxT[i] = max(maxT[i << 1], maxT[i << 1 | 1]);
    }

    while (M--) {
        int ql, qr; cin >> ql >> qr;
        auto [x, y] = query(ql - 1, qr);
        cout << x << ' ' << y << '\n';
    }
    return 0;
}