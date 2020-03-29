#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 3000;
const double eps = 1e-8;

int N;
int X[max_N], Y[max_N], R[max_N];
bool visited[max_N];

vector<int> adj[max_N];

void DFS(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v])
        DFS(v);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        cin >> N;
        loop(i, N) cin >> X[i] >> Y[i] >> R[i];

        memset(visited, 0, N);
        loop(i, N) adj[i].clear();

        loop(i, N) loop(j, i) {
            int dx = X[i] - X[j], dy = Y[i] - Y[j];
            double d = sqrt(dx * dx + dy * dy);
            if (R[i] + R[j] > d - eps) {
                adj[i].emplace_back(j);
                adj[j].emplace_back(i);
            }
        }

        int ans = 0;
        loop(i, N) if (!visited[i]) {
            ++ans;
            DFS(i);
        }
        cout << ans << '\n';
    }
    return 0;
}