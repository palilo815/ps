#include <bits/stdc++.h>
using namespace std;

const int max_N = 20000;

int arr[max_N + 1];
bool visited[max_N + 1];

int DFS(int u) {
    if (visited[u]) return 0;
    visited[u] = true;
    int ret = 1;
    ret += DFS(arr[u]);
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> arr[i];

    int ans = 1;
    for (int i = 1; i <= N; ++i) if (!visited[i])
        ans = lcm(ans, DFS(i));
    cout << ans;
    return 0;
}