#include <bits/stdc++.h>
using namespace std;

const int max_N = 20000;

int parent[max_N][2];   // [이전 나머지, 1or0]

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        memset(parent, -1, sizeof(parent));
        queue<int> q;
        
        int len = 1;
        parent[1 % N][0] = -2, parent[1 % N][1] = 1;
        q.emplace(1 % N), q.emplace(-1);
        while (1) {
            int u = q.front(); q.pop();
            if (u == -1) {
                if (++len > 101) break;
                q.emplace(-1); continue;
            }
            if (u == 0) break;

            int v = (10 * u) % N;   // add 0
            if (parent[v][0] == -1) {
                parent[v][0] = u, parent[v][1] = 0;
                q.emplace(v);
            }
            v = (v + 1) % N;        // add 1
            if (parent[v][0] == -1) {
                parent[v][0] = u, parent[v][1] = 1;
                q.emplace(v);
            }
        }

        if (parent[0][0] == -1) cout << "BRAK\n";
        else {
            int cur = 0;
            vector<int> ans;
            while (cur != -2) {
                auto [pre, x] = parent[cur];
                ans.emplace_back(x);
                cur = pre;
            }
            for (auto it = ans.rbegin(); it != ans.rend(); ++it)
                cout << *it;
            cout << '\n';
        }
    }
    return 0;
}