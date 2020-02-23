#include <bits/stdc++.h>
using namespace std;

const int max_N = 200;

int parent[max_N][2];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> ans;
    while (1) {
        int N; cin >> N;
        if (N == 0) break;
        memset(parent, -1, sizeof(parent));
        ans.clear();

        queue<int> q;
        parent[1 % N][0] = -2, parent[1 % N][1] = 1;
        q.emplace(1 % N);
        while (1) {
            int u = q.front(); q.pop();

            if (u == 0) break;

            int v = (10 * u) % N;
            if (parent[v][0] == -1) {
                parent[v][0] = u, parent[v][1] = 0;
                q.emplace(v);
            }
            v = (v + 1) % N;
            if (parent[v][0] == -1) {
                parent[v][0] = u, parent[v][1] = 1;
                q.emplace(v);
            }
        }
        
        int cur = 0;
        while (cur != -2) {
            auto [pre, x] = parent[cur];
            ans.emplace_back(x);
            cur = pre;
        }
        for (auto it = ans.rbegin(); it != ans.rend(); ++it)
            cout << *it;
        cout << '\n';
    }
    return 0;
}