#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e5;

int cnt[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, W; cin >> N >> W;
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        ++cnt[u], ++cnt[v];
    }
    cout << fixed << setprecision(9)
         << 1.0 * W / count(cnt + 2, cnt + N + 1, 1);
    return 0;
}