#include <bits/stdc++.h>
using namespace std;

const int mx = 1000;

int N, fenwick[mx + 1];

void update(int i) {
    for (; i <= N; i += i & -i)
        ++fenwick[i];
}
int read(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
void solve() {
    cin >> N;
    memset(fenwick + 1, 0, sizeof(int) * N);

    int ans = 0;
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        ans += x - 1 - read(x);
        update(x);
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}