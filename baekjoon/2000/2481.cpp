#include <bits/stdc++.h>
using namespace std;

const int max_N = 100001;

vector<int> adj[max_N];
int num[max_N];
int parent[max_N];

void print_path(int i) {
    if (i == -1) return;
    print_path(parent[i]);
    cout << i << ' ';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    // 않이... unordered_map 썼다가
    // TLE만 7번 받았다... ㅡㅡ.....
    vector<pair<int, int>> vt;

    int N, K; cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        string bit; cin >> bit;
        for (char b : bit) {
            num[i] <<= 1;
            num[i] |= (b == '1');
        }
        vt.emplace_back(num[i], i);
    }
    sort(vt.begin(), vt.end());

    for (int i = 1; i <= N; ++i) {
        int u = num[i];
        for (int k = 0; k < K; ++k) {
            int v = u ^ (1 << k);
            auto j = lower_bound(vt.begin(), vt.end(), make_pair(v, 0));
            if (j->first == v) adj[i].emplace_back(j->second);
        }
    }

    parent[1] = -1;

    queue<int> q;
    q.emplace(1);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (!parent[v]) {
            parent[v] = u;
            q.emplace(v);
        }
    }

    int Q; cin >> Q;
    while (Q--) {
        int dst; cin >> dst;
        if (parent[dst]) print_path(dst);
        else cout << -1;
        cout << '\n';
    }
    return 0;
}