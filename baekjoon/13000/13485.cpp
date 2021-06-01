#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int row = 10;

    int n;
    cin >> n;

    array<string, row> mat;
    for (auto& x : mat) cin >> x;

    array<vector<bool>, row> ok;
    for (int i = 0; i < row; ++i) {
        ok[i].resize(n);
        ok[i].back() = mat[i].back() == '.';
    }

    for (int c = n - 1; c--;) {
        ok[0][c] = mat[0][c] == '.' && (ok[0][c + 1] || ok[1][c + 1]);
        for (int r = 1; r < row - 1; ++r)
            ok[r][c] = mat[r][c] == '.' && (ok[r - 1][c + 1] || ok[r + 1][c + 1]);
        ok[9][c] = mat[9][c] == '.' && (ok[8][c + 1] || ok[9][c + 1]);
    }

    assert(ok[row - 1][0]);

    vector<pair<int, int>> ans;
    for (int r = row - 1, c = 0; c < n - 1; ++c) {
        if ((r == row - 1 && ok[r][c + 1]) || (r != row - 1 && ok[r + 1][c + 1])) {
            if (r != row - 1) ++r;
        } else {
            if (r) --r;
            ans.emplace_back(c, 1);
        }
    }

    cout << ans.size() << '\n';
    for (const auto& [t, x] : ans)
        cout << t << ' ' << x << '\n';
}