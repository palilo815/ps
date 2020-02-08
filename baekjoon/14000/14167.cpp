#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;

int x[max_N], y[max_N], dist[max_N];
bool f[max_N];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> x[i] >> y[i];
    loop(i, N) dist[i] = 1 << 30;
    dist[0] = 0;

    int ans = 0, cnt = N;
    while (cnt--) {
        int k = -1;
        loop(i, N) if (!f[i] && (k == -1 || dist[i] < dist[k])) k = i;
        f[k] = true;
        if (dist[k] > ans) ans = dist[k];

        loop(i, N) if (!f[i]) {
            int dx = x[k] - x[i], dy = y[k] - y[i];
            int d = dx * dx + dy * dy;
            if (dist[i] > d) dist[i] = d;
        }
    }
    cout << ans;
    return 0;
}