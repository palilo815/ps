#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (auto& s : grid) cin >> s;

    int ans = 0;
    if (n < 3 || m < 3) {
        if (n < 3)
            for (int i = 1; i < m - 1; ++i)
                ans += grid[0][i] == '.' && (n == 2 ? grid[1][i] == '.' : true);
        if (m < 3)
            for (int i = 1; i < n - 1; ++i)
                ans += grid[i][0] == '.' && (m == 2 ? grid[i][1] == '.' : true);
    } else {
        ans += accumulate(grid.begin() + 1, grid.end() - 1, 0, [&](auto& sum, auto& s) {
            return sum + count(s.begin() + 1, s.end() - 1, '.');
        });
        ans += none_of(grid[0].begin() + 1, grid[0].end() - 1, [&](auto& x) { return x == '#'; }) &&
               none_of(grid[0].begin() + 1, grid[0].end() - 1, [&](auto& x) { return x == '#'; }) &&
               none_of(grid.begin() + 1, grid.end() - 1, [&](auto& s) {
                   return s.front() == '#' || s.back() == '#';
               });
    }
    cout << ans;
}