#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int u = 0, v, sz; u != n; ++u) {
        for (cin >> sz; sz--;) {
            cin >> v, --v;
            adj[u].emplace_back(v);
        }
    }

    vector<char> team(n);
    vector<int> stk;
    auto dfs = [&](int s, char s_team) {
        team[s] = s_team;
        stk.emplace_back(s);
        while (!stk.empty()) {
            const auto u = stk.back();
            stk.pop_back();

            for (const auto& v : adj[u]) {
                assert(team[v] != team[u]);
                if (!team[v]) {
                    team[v] = team[u] == 'B' ? 'W' : 'B';
                    stk.emplace_back(v);
                }
            }
        }
    };

    for (int i = 0; i < n; ++i)
        if (!team[i])
            dfs(i, i ? 'B' : 'W');

    cout << count(team.begin(), team.end(), 'B') << '\n';
    for (int i = 0; i < n; ++i)
        if (team[i] == 'B')
            cout << i + 1 << ' ';
    cout << '\n';

    cout << count(team.begin(), team.end(), 'W') << '\n';
    for (int i = 0; i < n; ++i)
        if (team[i] == 'W')
            cout << i + 1 << ' ';
    cout << '\n';
}