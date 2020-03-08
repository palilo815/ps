#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int parent[max_N + 1];
int soldier[max_N + 1];

int find_rt(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> soldier[i];
        parent[i] = i;
    }

    while (M--) {
        int q, a, b; cin >> q >> a >> b;
        a = find_rt(a), b = find_rt(b);
        if (q == 1) {
            parent[a] = b;
            soldier[b] += soldier[a];
        }
        else {
            if (soldier[a] > soldier[b]) {
                parent[b] = a;
                soldier[a] -= soldier[b];
            }
            else if (soldier[a] < soldier[b]) {
                parent[a] = b;
                soldier[b] -= soldier[a];
            }
            else soldier[a] = soldier[b] = 0;
        }
    }
    vector<int> ans;
    for (int i = 1; i <= N; ++i) {
        int rt = find_rt(i);
        if (soldier[rt]) {
            ans.emplace_back(soldier[rt]);
            soldier[rt] = 0;
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int x : ans) cout << x << ' ';
    return 0;
}