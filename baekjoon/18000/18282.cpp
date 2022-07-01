#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> couple(n << 1);
    for (int i = n, u, v; i--;) {
        cin >> u >> v, --u, --v;
        couple[u] = v, couple[v] = u;
    }
    string food(n << 1, 0);
    for (int i = 0; i < n << 1; ++i) {
        if (food[i]) continue;
        food[i] = 'A';
        for (int u = i;;) {
            if (!food[u ^ 1]) {
                food[u ^ 1] = food[u] == 'A' ? 'B' : 'A';
                u ^= 1;
            } else if (!food[couple[u]]) {
                food[couple[u]] = food[u] == 'A' ? 'B' : 'A';
                u = couple[u];
            } else {
                break;
            }
        }
    }
    cout << food;
}
