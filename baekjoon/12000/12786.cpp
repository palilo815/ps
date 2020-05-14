#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const size_t sz = sizeof(int) * 20;
const int INF = 0x3f3f3f3f;

int DP[21];
int tmp[21];

int jump(int u, int v) {
    if (u == v || u + 1 == v || u - 1 == v || min(20, u * 2) == v)
        return 0;
    return 1;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, T; cin >> N >> T;
    memset(DP + 1, -1, sz);
    DP[1] = 0;

    while (N--) {
        memset(tmp + 1, -1, sz);

        int cnt; cin >> cnt;
        while (cnt--) {
            int x; cin >> x;
            tmp[x] = INF;
        }

        LOOP(u, 20) if (DP[u] != -1)
            LOOP(v, 20) if (tmp[v] != -1)
                tmp[v] = min(tmp[v], DP[u] + jump(u, v));

        memcpy(DP + 1, tmp + 1, sz);
    }

    int ans = T + 1;
    LOOP(i, 20) if (DP[i] != -1)
        ans = min(ans, DP[i]);
    cout << (ans > T ? -1 : ans);
    return 0;
}