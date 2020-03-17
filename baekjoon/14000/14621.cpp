#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 1000;

char gender[max_N + 1];
int parent[max_N + 1];

int find_rt(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    LOOP(i, N) parent[i] = i;
    LOOP(i, N) cin >> gender[i];

    vector<tup> edge;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        if (gender[u] != gender[v])
            edge.emplace_back(w, u, v);
    }
    sort(edge.begin(), edge.end());

    int ans = 0;
    for (auto [w, u, v] : edge) {
        u = find_rt(u), v = find_rt(v);
        if (u != v) {
            parent[u] = v;
            ans += w;
        }
    }

    int rt = find_rt(1);
    LOOP(i, N) if (find_rt(i) != rt) {
        ans = -1;
        break;
    }
    cout << ans;
    return 0;
}