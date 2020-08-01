#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 2e3;

int a[mxN], x[mxN], y[mxN];

int ccw(int u, int v) {
    int ret = (x[u] - x[a[0]]) * (y[v] - y[a[0]]) -
              (y[u] - y[a[0]]) * (x[v] - x[a[0]]);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int dist(int v) {
    int dx = x[a[0]] - x[v], dy = y[a[0]] - y[v];
    return dx * dx + dy * dy;
}
void solve() {
    int N; cin >> N;
    loop(i, N) cin >> x[i] >> y[i];
    iota(a, a + N, 0);

    swap(a[0], *min_element(a, a + N, [&](int& a, int& b) {
        return x[a] == x[b] ? y[a] < y[b] : x[a] < x[b];
    }));
    sort(a + 1, a + N, [&](int& a, int& b) {
        int ret = ccw(a, b);
        return ret ? ret == 1 : dist(a) < dist(b);
    });

    int i = N - 2;
    while (!ccw(a[N - 1], a[i])) --i;
    reverse(a + i + 1, a + N);

    loop(i, N) cout << a[i] << ' '; cout << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}