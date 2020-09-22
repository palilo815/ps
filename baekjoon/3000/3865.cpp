#include <bits/stdc++.h>
using namespace std;

const int mx = 100 * 10 + 1;

vector<int> adj[mx];
bool visited[mx];
char s[16 * 11 + 1];

int dfs(int u) {
    visited[u] = true;
    if (adj[u].empty()) return 1;

    int ret = 0;
    for (int& v : adj[u])
        if (!visited[v])
            ret += dfs(v);
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int N;;) {
        cin >> N;
        if (!N) break;
        for (int i = 0; i < mx; ++i)
            adj[i].clear();
        memset(visited, 0, sizeof(visited));

        unordered_map<string, int> mp;
        for (int i = 0; N--;) {
            cin >> s;
            vector<int> vt;
            for (char *it = s, *nxt, *last = s + strlen(s); it != last; it = nxt + 1) {
                nxt = find_if(it, last, [&](auto& c) { return c == ':' || c == ',' || c == '.'; });
                string token = string(it, nxt - it);
                if (!mp[token]) mp[token] = ++i;
                vt.emplace_back(mp[token]);
            }
            for (int i = 1; i < vt.size(); ++i)
                adj[vt[0]].emplace_back(vt[i]);
        }
        cout << dfs(1) << '\n';
    }
    return 0;
}