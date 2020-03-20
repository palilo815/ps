#include <iostream>
using namespace std;

const int max_N = 1000000;

int parent[max_N + 1];
int cnt[max_N + 1];

int _find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = _find(parent[u]);
}
void _merge(int u, int v) {
    u = _find(u), v = _find(v);
    if (u == v) return;
    parent[u] = v;
    cnt[v] += cnt[u];
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    for (int i = 1; i <= max_N; ++i)
        parent[i] = i, cnt[i] = 1;
    int N; cin >> N;
    while (N--) {
        char q; cin >> q;
        if (q == 'I') {
            int u, v; cin >> u >> v;
            _merge(u, v);
        }
        else{
            int idx; cin >> idx;
            cout << cnt[_find(idx)] << '\n';
        }
    }
    return 0;
}