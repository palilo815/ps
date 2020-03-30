#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;
typedef long long ll;

const int mod = 1e9;
const int max_N = 100000;
const int max_M = 100000;

tup edge[max_M];
int parent[max_N];
int child[max_N];

int find_rt(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    ll sum = 0;
    loop(i, M) {
        int u, v, w; cin >> u >> v >> w;
        sum += w;
        edge[i] = { w,u - 1,v - 1 };
    }

    sort(edge, edge + M, greater<tup>());
    loop(i, N) parent[i] = i;
    loop(i, N) child[i] = 1;

    ll ans = 0;
    loop(i, M) {
        auto [w, u, v] = edge[i];
        u = find_rt(u), v = find_rt(v);
        if (u != v) {
            ans += (sum % mod) * ((ll)child[u] * child[v] % mod) % mod;
            ans %= mod;
            parent[u] = v;
            child[v] += child[u];
        }
        sum -= w;
    }
    cout << ans;
    return 0;
}