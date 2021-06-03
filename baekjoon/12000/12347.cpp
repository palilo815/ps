#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;

bool solve() {
    __gnu_pbds::gp_hash_table<string, int> mp;

    int m;
    cin >> m;

    int n = 0;
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) {
        string s0, s1;
        cin >> s0 >> s1;

        if (mp.find(s0) == mp.end()) mp[s0] = n++;
        if (mp.find(s1) == mp.end()) mp[s1] = n++;
        u = mp[s0], v = mp[s1];
    }

    vector<vector<int>> adj(n);
    for (const auto& [u, v] : edges) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<char> colour(n); // null, 'o', 'x'
    vector<int> stk;

    for (int i = 0; i < n; ++i) {
        if (colour[i]) continue;
        stk.emplace_back(i);
        colour[i] = 'o';

        while (!stk.empty()) {
            const auto u = stk.back();
            stk.pop_back();

            for (const auto& v : adj[u]) {
                if (colour[v]) {
                    if (colour[u] == colour[v])
                        return false;
                } else {
                    colour[v] = colour[u] == 'o' ? 'x' : 'o';
                    stk.emplace_back(v);
                }
            }
        }
    }
    return true;
};
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
        cout << "Case #" << t << ": " << (solve() ? "Yes\n" : "No\n");
}