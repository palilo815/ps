#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<string> a(n);
    for (auto& x : a) cin >> x;

    vector<int> ord(n);
    for (auto& x : ord) cin >> x, --x;

    {
        vector<string> sorted(n);
        for (int i = 0; i < n; ++i)
            sorted[i] = a[ord[i]];
        a = sorted;
    }

    array<array<bool, 26>, 26> adj {};
    array<int, 26> indegree {};

    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            size_t it = 0;
            while (it != a[i].size() && it != a[j].size() && a[i][it] == a[j][it])
                ++it;
            if (it == a[j].size()) return cout << "NE", 0;
            if (it == a[i].size()) continue;
            if (!adj[a[i][it] - 'a'][a[j][it] - 'a']) {
                adj[a[i][it] - 'a'][a[j][it] - 'a'] = true;
                ++indegree[a[j][it] - 'a'];
            }
        }

    queue<int> q;
    for (int i = 0; i < 26; ++i)
        if (indegree[i] == 0)
            q.emplace(i);

    string ans;
    ans.resize(26);

    char alpha = 'a';

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        ans[u] = alpha++;
        for (int v = 0; v < 26; ++v)
            if (adj[u][v] && --indegree[v] == 0)
                q.emplace(v);
    }

    if (alpha != 'z' + 1) cout << "NE";
    else {
        cout << "DA\n";
        cout << ans;
    }
}