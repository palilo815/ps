#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> p;
typedef tuple<ll, int, int> tup;
const int max_N = 1000;

int parent[max_N];
p V[max_N];
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

    int N, M; cin >> N >> M;
    loop(i, N) parent[i] = i;
    loop(i, N) cin >> V[i].first >> V[i].second;
    int idx = 0;
    loop(i, N - 1) for (int j = i + 1; j < N; ++j) {
        ll dx = V[i].first - V[j].first;
        ll dy = V[i].second - V[j].second;
        E[idx++] = { dx * dx + dy * dy,i,j };
    }
    sort(E, E + idx);

    while (M--) {
        int u, v; cin >> u >> v;
        u = find_rt(u - 1), v = find_rt(v - 1);
        parent[u] = v;
    }

    double ans = 0;
    loop(i, idx) {
        int u = get<1>(E[i]), v = get<2>(E[i]);
        u = find_rt(u), v = find_rt(v);
        if (u == v) continue;
        parent[u] = v;
        ans += sqrt(get<0>(E[i]));
    }
    cout << fixed << setprecision(2) << ans;
    return 0;
}