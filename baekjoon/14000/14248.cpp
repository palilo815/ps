#include <bits/stdc++.h>
using namespace std;

const int mx = 1e5 + 1;

int a[mx];
bool visited[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> a[i];

    int src; cin >> src;
    visited[src] = true;

    queue<int> q;
    q.emplace(src);

    for (int u, v; !q.empty();) {
        u = q.front(); q.pop();
        v = u - a[u];
        if (v > 0 && !visited[v]) {
            visited[v] = true;
            q.emplace(v);
        }
        v = u + a[u];
        if (v <= N && !visited[v]) {
            visited[v] = true;
            q.emplace(v);
        }
    }
    cout << count(visited + 1, visited + N + 1, true);
    return 0;
}