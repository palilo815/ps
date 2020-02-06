#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 2000;

int dist[max_N];
int x[max_N], y[max_N];
bool v[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, C; cin >> N >> C;
    loop(i, N) cin >> x[i] >> y[i];
    loop(i, N) dist[i] = (1 << 30);

    dist[0] = 0;
    int ans = 0;
    loop(t, N) {
        int k = -1;
        loop(i, N) if (!v[i] && (k == -1 || dist[i] < dist[k])) k = i;
        if (dist[k] == (1 << 30)) {
            ans = -1;
            break;
        }
        ans += dist[k];
        v[k] = true;
        loop(i, N) if (!v[i]) {
            int dx = x[k] - x[i], dy = y[k] - y[i];
            int d = dx * dx + dy * dy;
            if (d >= C && d < dist[i]) dist[i] = d;
        }
    }
    cout << ans;
    return 0;
}
