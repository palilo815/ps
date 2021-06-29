#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m, v, h;
    cin >> n >> m >> v >> h;

    vector<int> v_vec(v), h_vec(h);
    for (auto& x : v_vec) cin >> x;
    for (auto& x : h_vec) cin >> x;

    vector grid(n, string(m, 'B'));
    {
        bool is_white = false;
        int cur = 0;
        for (const auto& x : v_vec) {
            if (is_white)
                for (int i = cur; i < cur + x; ++i)
                    fill(grid[i].begin(), grid[i].end(), 'W');
            is_white ^= true;
            cur += x;
        }
    }
    {
        bool is_white = false;
        int cur = 0;
        for (const auto& x : h_vec) {
            if (is_white)
                for (auto& s : grid)
                    for (int i = cur; i < cur + x; ++i)
                        s[i] = s[i] == 'B' ? 'W' : 'B';
            is_white ^= true;
            cur += x;
        }
    }

    for (const auto& x : grid)
        cout << x << '\n';
}