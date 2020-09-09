#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4 + 1;

int a[mxN];
bool visited[mxN];

void solve() {
    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> a[i];

    memset(visited + 1, 0, N);

    for (int u = 1, ans = 0;; ++ans, u = a[u]) {
        if (visited[u]) {cout << "0\n"; break;}
        if (u == N) {cout << ans << '\n'; break;}
        visited[u] = true;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}