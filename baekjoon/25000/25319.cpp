#include <bits/stdc++.h>

constexpr int MAX_N = 50;

std::array<std::array<char, MAX_N>, MAX_N> grid;

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, l;
    cin >> n >> m >> l;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }
    string s;
    cin >> s;
    vector<vector<pair<int, int>>> pos(l);
    for (int k = 0; k < l; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == s[k]) {
                    pos[k].emplace_back(i, j);
                }
            }
        }
    }
    vector<pair<int, int>> path, cur(l);
    for (int px = 0, py = 0;;) {
        cur.clear();
        for (int i = 0; i < l; ++i) {
            pos[i].erase(remove_if(pos[i].begin(), pos[i].end(), [&](const auto& x) {
                return !grid[x.first][x.second];
            }),
                pos[i].end());
            if (pos[i].empty()) break;
            const auto nxt = *min_element(pos[i].begin(), pos[i].end(), [&](const auto& lhs, const auto& rhs) {
                return abs(px - lhs.first) + abs(py - lhs.second) < abs(px - rhs.first) + abs(py - rhs.second);
            });
            cur.emplace_back(nxt);
            px = nxt.first, py = nxt.second;
            grid[px][py] = 0;
        }
        if (static_cast<int>(cur.size()) != l) break;
        path.insert(path.end(), cur.begin(), cur.end());
    }
    int px = 0, py = 0;
    string ans;
    for (auto [x, y] : path) {
        while (px < x) ans.push_back('D'), ++px;
        while (px > x) ans.push_back('U'), --px;
        while (py < y) ans.push_back('R'), ++py;
        while (py > y) ans.push_back('L'), --py;
        ans.push_back('P');
    }
    while (px < n - 1) ans.push_back('D'), ++px;
    while (py < m - 1) ans.push_back('R'), ++py;
    cout << path.size() / l << ' ' << ans.size() << '\n'
         << ans;
}
