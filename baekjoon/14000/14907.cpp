#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    array<vector<int>, 26> adj;
    array<int, 26> w, need;
    w.fill(-1), need.fill(0);
    for (string s; !cin.eof();) {
        getline(cin, s);
        stringstream sin(s);
        char u, v;
        sin >> v;
        sin >> w[v - 'A'];
        while (sin >> u) {
            adj[u - 'A'].emplace_back(v - 'A');
            ++need[v - 'A'];
        }
    }
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (~w[i] && !need[i]) {
            q.emplace(i);
        }
    }
    array<int, 26> dp {};
    while (!q.empty()) {
        const auto u = q.front();
        q.pop();
        dp[u] += w[u];
        for (const auto& v : adj[u]) {
            chmax(dp[v], dp[u]);
            if (--need[v] == 0) {
                q.emplace(v);
            }
        }
    }
    cout << *max_element(dp.begin(), dp.end());
}