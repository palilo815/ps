#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_N = 1000;

bool v[max_N];
int adj[max_N][max_N];
int cost[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> adj[i][j];

    fill(cost + 1, cost + N, INT_MAX);
    int cnt = N;

    ll ans = 0;
    while (cnt--) {
        int k = -1;
        loop(i, N) if (!v[i] && (k == -1 || cost[i] < cost[k]))
            k = i;

        assert(k != -1);
        v[k] = true;
        ans += cost[k];

        loop(i, N) if (!v[i])
            cost[i] = min(cost[i], adj[k][i]);
    }
    cout << ans;
    return 0;
}