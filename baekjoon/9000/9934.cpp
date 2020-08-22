#include <bits/stdc++.h>
using namespace std;

const int mx = 10;

vector<int> tree[mx];
int a[(1 << mx) - 1];

void solve(int s, int e, int i) {
    if (s == e) return;
    int m = (s + e) >> 1;
    tree[i].emplace_back(a[m]);
    solve(s, m, i + 1);
    solve(m + 1, e, i + 1);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int K; cin >> K;
    for (int i = 0; i < (1 << K) - 1; ++i)
        cin >> a[i];

    solve(0, (1 << K) - 1, 0);

    for (int i = 0; i < K; ++i) {
        for (int& x : tree[i]) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}