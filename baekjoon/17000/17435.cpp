#include <bits/stdc++.h>
using namespace std;

class jump_table {
public:
    vector<vector<int>> jump;
    int n, row;

    jump_table(const vector<int>& vt, int max_step) {
        n = vt.size(), row = 32 - __builtin_clz(max_step);

        jump.resize(row);
        jump[0] = move(vt);

        for (int i = 1; i < row; ++i) {
            jump[i].resize(n);
            for (int j = 0; j < n; ++j)
                jump[i][j] = jump[i - 1][jump[i - 1][j]];
        }
    }
    int query(int x, int step) {
        for (int i = row - 1; ~i; --i)
            if (step & (1 << i))
                x = jump[i][x];
        return x;
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int m;
    cin >> m;

    vector<int> f(m);
    for (int& x : f) cin >> x;
    for (int& x : f) --x;

    jump_table table(f, 5e5);

    int q;
    cin >> q;

    for (int n, x; q--;) {
        cin >> n >> x;
        cout << table.query(x - 1, n) + 1 << '\n';
    }
}