#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;

int x[max_N], y[max_N];
int dist[max_N];
bool conn[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    while (1) {
        int N; cin >> N;
        if (!N) break;
        loop(i, N) cin >> x[i] >> y[i];

        memset(conn, 0, N);
        memset(dist, 0x3f, sizeof(int) * N);
        dist[0] = 0;
        
        double ans = 0;
        int cnt = N;
        while (cnt--) {
            int k = -1;
            loop(i, N) if (!conn[i] && (k == -1 || dist[i] < dist[k]))
                k = i;

            ans += sqrt(dist[k]);
            conn[k] = true;

            loop(i, N) if (!conn[i]) {
                int dx = x[i] - x[k], dy = y[i] - y[k];
                dist[i] = min(dist[i], dx * dx + dy * dy);
            }
        }
        cout << fixed << setprecision(2) << ans << '\n';
    }
    return 0;
}