#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int adj[5][2] = { -1,0,0,-1,0,0,0,1,1,0 };

ll DP[5];
ll tmp[5];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, sx, sy, prv_x, prv_y;
    cin >> N >> sx >> sy >> prv_x >> prv_y;
    loop(i, 5) DP[i] = abs(sx - prv_x - adj[i][0]) + abs(sy - prv_y - adj[i][1]);

    while (--N) {
        int x, y; cin >> x >> y;
        memset(tmp, 0x3f, sizeof(ll) * 5);

        loop(i, 5) loop(j, 5)
            tmp[i] = min(tmp[i], DP[j] + abs(x + adj[i][0] - (prv_x + adj[j][0])) + abs(y + adj[i][1] - (prv_y + adj[j][1])));

        memcpy(DP, tmp, sizeof(ll) * 5);
        prv_x = x, prv_y = y;
    }
    cout << *min_element(DP, DP + 5);
    return 0;
}