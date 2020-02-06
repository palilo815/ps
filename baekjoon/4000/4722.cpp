#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;
const int max_N = 1000;

int parent[max_N];
int V[max_N][2];
tup E[(max_N - 1) * (max_N / 2)];
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while(1){
        int N; cin >> N;
        if (N == 0) break;
        loop(i, N) parent[i] = i;
        loop(i, N) cin >> V[i][0] >> V[i][1];

        int idx = 0;
        loop(i, N - 1) for (int j = i + 1; j < N; ++j) {
            int dx = V[i][0] - V[j][0], dy = V[i][1] - V[j][1];
            E[idx++] = { dx * dx + dy * dy,i,j };
        }
        sort(E, E + idx);

        double ans = 0;
        loop(i, idx) {
            int u = get<1>(E[i]), v = get<2>(E[i]);
            u = find_rt(u), v = find_rt(v);
            if (u == v) continue;
            parent[u] = v;
            ans += sqrt(get<0>(E[i]));
        }
        cout << fixed << setprecision(2) << ans << '\n';
    }
    return 0;
}