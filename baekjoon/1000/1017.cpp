#include <bits/stdc++.h>
using namespace std;

const int max_num = 1000;

vector<int> adj[max_num + 1];

int first;
bool visited[max_num + 1];
int match[max_num + 1];

bool is_prime(int n)
{
    if (n <= 2) return true;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}
bool DFS(int u)
{
    if (visited[u]) return false;
    visited[u] = true;
    for(int v : adj[u])
        if (!match[v] || (match[v] != first && DFS(match[v]))) {
            match[v] = u;
            return true;
        }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> odd, even;
    int N; cin >> N;

    cin >> first;
    for (int i = 1; i < N; ++i) {
        int x; cin >> x;
        if (x % 2) odd.emplace_back(x);
        else even.emplace_back(x);
    }

    vector<int>& U = (first % 2) ? odd : even;
    vector<int>& V = (first % 2) ? even : odd;

    for (int u : U) for (int v : V)
        if (is_prime(u + v))
            adj[u].emplace_back(v);

    vector<int> ans;
    for (int v : V)
        if (is_prime(first + v)) {
            memset(match, 0, sizeof(match));
            match[v] = first;
            int cnt = 1;
            for (int u : U) {
                memset(visited, 0, sizeof(visited));
                if (DFS(u)) ++cnt;
            }
            if (cnt == N / 2) ans.push_back(v);
        }

    sort(ans.begin(), ans.end());
    if (ans.empty()) cout << -1;
    else for (int x : ans) cout << x << ' ';
    return 0;
}