#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr array<pair<int, int>, 4> mov {{{1, 0}, {0, -1}, {-1, 0}, {0, 1}}};
    int n;
    string s;
    cin >> n >> s;
    array<array<char, 17>, 17> grid;
    vector<pair<int, int>> up, down;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'Z') {
                down.emplace_back(i, j);
            }
        }
    }
    array<array<bool, 17>, 17> light {};
    vector<pair<int, int>> up_q, down_q;
    int x = 1, y = 1, f = 0;
    for (const auto& c : s) {
        if (c == 'L') {
            f = f ? f - 1 : 3;
        } else if (c == 'R') {
            f = f == 3 ? 0 : f + 1;
        } else {
            if (const auto xx = x + mov[f].first, yy = y + mov[f].second;
                xx && xx != n + 1 && yy && yy != n + 1) {
                x = xx, y = yy;
            }
            if (grid[x][y] == 'S') {
                light[x - 1][y - 1] = light[x - 1][y] = light[x - 1][y + 1] = true;
                light[x][y - 1] = light[x][y] = light[x][y + 1] = true;
                light[x + 1][y - 1] = light[x + 1][y] = light[x + 1][y + 1] = true;
            }
        }
        if (!light[x][y] &&
            (find(up.begin(), up.end(), pair(x, y)) != up.end() || find(down.begin(), down.end(), pair(x, y)) != down.end())) {
            return cout << "Aaaaaah!", 0;
        }
        for (auto it = up.begin(); it != up.end();) {
            if (it->first == 1) {
                down_q.emplace_back(*it);
                it = up.erase(it);
            } else {
                --it->first;
                ++it;
            }
        }
        for (auto it = down.begin(); it != down.end();) {
            if (it->first == n) {
                up_q.emplace_back(*it);
                it = down.erase(it);
            } else {
                ++it->first;
                ++it;
            }
        }
        up.insert(up.end(), up_q.begin(), up_q.end());
        down.insert(down.end(), down_q.begin(), down_q.end());
        if (!light[x][y] &&
            (find(up.begin(), up.end(), pair(x, y)) != up.end() || find(down.begin(), down.end(), pair(x, y)) != down.end())) {
            return cout << "Aaaaaah!", 0;
        }
        up_q.clear(), down_q.clear();
    }
    cout << "Phew...";
}