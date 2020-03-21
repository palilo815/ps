#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 4001;

bool sieve[8486];
int X[max_N], Y[max_N];
int dist[max_N];
bool v[max_N];

int func(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2, dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i < 8486; ++i)
        if (!sieve[i])
            for (int j = i * i; j < 8486; j += i)
                sieve[j] = true;

    int sx, sy, dx, dy, N;
    cin >> sx >> sy >> dx >> dy >> N;
    loop(i, N) cin >> X[i] >> Y[i];

    X[N] = dx, Y[N] = dy;
    ++N;

    loop(i, N) {
        int d = func(sx, sy, X[i], Y[i]);
        dist[i] = (sieve[d] ? INT_MAX : d);
    }
    
    int ans = -1;
    while (1) {
        int k = -1;
        loop(i, N) if (!v[i] && (k == -1 || dist[i] < dist[k]))
            k = i;

        if (dist[k] == INT_MAX) break;
        if (k == N - 1) { ans = dist[k]; break; }

        v[k] = true;
        loop(i, N) if (!v[i]) {
            int d = func(X[k], Y[k], X[i], Y[i]);
            if (!sieve[d] && dist[i] > d + dist[k])
                dist[i] = d + dist[k];
        }
    }
    cout << ans;
    return 0;
}