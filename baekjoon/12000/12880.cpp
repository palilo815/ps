#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 50;

int adj[mxN][mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    loop(i, n) loop(j, n) cin >> adj[i][j];

    vector<int> ord(n * n);
    loop(i, n) move(adj[i], adj[i] + n, ord.begin() + i * n);
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());
    int sz = ord.size();

    vector<int> low(n), disc(n);
    auto valid = [&](const int mn, const int mx) {
        int t = 0;
        fill(low.begin(), low.end(), 0);
        fill(disc.begin(), disc.end(), -1);

        function<bool(int)> dfs = [&](int u) {
            low[u] = disc[u] = t++;
            loop(v, n) {
                if (adj[u][v] < mn || mx < adj[u][v]) continue;
                if (disc[v] == -1) {
                    if (dfs(v)) return true;
                    low[u] = min(low[u], low[v]);
                } else
                    low[u] = min(low[u], disc[v]);
            }
            return low[u] == disc[u];
        };

        low[0] = disc[0] = t++;
        loop(v, n) {
            if (adj[0][v] < mn || mx < adj[0][v]) continue;
            if (disc[v] == -1) {
                if (dfs(v)) return false;
                low[0] = min(low[0], low[v]);
            } else
                low[0] = min(low[0], disc[v]);
        }
        return low[0] == disc[0] && t == n;
    };

    int ans = INT_MAX;
    for (int i = 0; i < sz; ++i) {
        int lo = i, hi = sz;
        while (lo != hi) {
            int mid = (lo + hi) >> 1;
            valid(ord[i], ord[mid]) ? hi = mid : lo = mid + 1;
        }
        if (lo != sz) ans = min(ans, ord[lo] - ord[i]);
    }
    cout << ans;
}