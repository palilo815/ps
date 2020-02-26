#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;

int x[max_N + 2], y[max_N + 2];
bool visited[max_N + 2];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        loop(i, N + 2) cin >> x[i] >> y[i];

        bool happy = false;
        memset(visited, 0, sizeof(visited));
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == N + 1) {
                happy = true;
                break;
            }
            loop(v, N + 2) if (!visited[v]) {
                int d = abs(x[u] - x[v]) + abs(y[u] - y[v]);
                if (d <= 1000) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << (happy ? "happy" : "sad") << '\n';
    }
    return 0;
}