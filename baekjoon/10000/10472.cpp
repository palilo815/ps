#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[9] = {0x1a0, 0x1d0, 0xc8, 0x134, 0xba, 0x59, 0x26, 0x17, 0xb};

bool visited[0x200];

void solve() {
    int dst = 0;
    loop(i, 9) {
        char c; cin >> c;
        dst <<= 1;
        if (c == '*') dst |= 1;
    }

    memset(visited, 0, sizeof(visited));
    visited[0] = true;

    queue<int> q;
    q.emplace(0), q.emplace(-1);

    int ans = 0;
    for (;;) {
        int u = q.front(); q.pop();
        if (u == -1) {++ans; q.emplace(-1); continue;}
        if (u == dst) break;

        loop(i, 9) {
            int v = u ^ mov[i];
            if (!visited[v]) q.emplace(v), visited[v] = true;
        }
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