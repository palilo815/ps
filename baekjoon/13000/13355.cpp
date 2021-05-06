#include <bits/stdc++.h>
using namespace std;

enum {
    par = 26,
    tab = 27
};

struct trie_node {
    int dist;
    array<int, 28> adj; // [0, 26) = child, 26 = parrent, 27 = tab
    trie_node() { memset(this, -1, sizeof(trie_node)); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<trie_node> trie(1);
    trie.reserve(1000000);
    int node_count = 1;
    trie[0].adj[tab] = 0;

    auto add = [&](string& s) {
        int cur = 0, sz = s.size();
        for (int i = 0; i < sz; ++i) {
            int key = s[i] - 'a';
            if (trie[cur].adj[key] == -1) {
                trie.emplace_back();
                trie[node_count].adj[par] = cur;
                trie[cur].adj[key] = node_count++;
            }
            cur = trie[cur].adj[key];
        }
        int last_idx = exchange(cur, 0);
        for (int i = 0; i < sz; ++i) {
            cur = trie[cur].adj[s[i] - 'a'];
            if (trie[cur].adj[tab] == -1)
                trie[cur].adj[tab] = last_idx;
        }
    };
    auto query = [&](string& s) {
        int cur = 0, i = 0, sz = s.size();
        while (i < sz) {
            int key = s[i] - 'a';
            if (trie[cur].adj[key] == -1)
                break;

            cur = trie[cur].adj[key];
            ++i;
        }
        return trie[cur].dist + sz - i;
    };

    for (int i = n; i--;) {
        string s;
        cin >> s;
        add(s);
    }

    { // BFS
        queue<int> q;
        q.emplace(0);
        trie[0].dist = 0;

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& v : trie[u].adj)
                if (v != -1 && trie[v].dist == -1) {
                    trie[v].dist = trie[u].dist + 1;
                    q.emplace(v);
                }
        }
    }

    for (int i = m; i--;) {
        string s;
        cin >> s;
        cout << query(s) << '\n';
    }
}