#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, h;
    cin >> n >> m >> h;
    vector<string> proj1(n), proj2(n);
    for (auto& x : proj1) {
        cin >> x;
    }
    for (auto& x : proj2) {
        cin >> x;
    }
    vector block(n, vector(m, vector(h, true)));
    auto get_ans = [&]() {
        vector<tuple<int, int, int>> ans;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < h; ++k) {
                    if (block[i][j][k]) {
                        ans.emplace_back(i, j, k);
                    }
                }
            }
        }
        return ans;
    };
    // maximize
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (proj1[i][j] == '0') {
                fill(block[i][j].begin(), block[i][j].end(), false);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < h; ++k) {
            if (proj2[i][k] == '0') {
                for (int j = 0; j < m; ++j) {
                    block[i][j][k] = false;
                }
            }
        }
    }
    const auto maximize = get_ans();
    // minimize
    for (auto& x : block) {
        for (auto& y : x) {
            fill(y.begin(), y.end(), false);
        }
    }
    vector<int> check_m(m), check_h(h);
    for (int i = 0; i < n; ++i) {
        check_m.clear(), check_h.clear();
        for (int j = m; j--;) {
            if (proj1[i][j] == '1') {
                check_m.emplace_back(j);
            }
        }
        for (int k = h; k--;) {
            if (proj2[i][k] == '1') {
                check_h.emplace_back(k);
            }
        }
        if (check_m.empty() ^ check_h.empty()) {
            return cout << -1, 0;
        }
        while (check_m.size() > check_h.size()) {
            block[i][check_m.back()][check_h.back()] = true;
            check_m.pop_back();
        }
        while (check_m.size() < check_h.size()) {
            block[i][check_m.back()][check_h.back()] = true;
            check_h.pop_back();
        }
        for (int it = check_m.size(); it--;) {
            block[i][check_m[it]][check_h[it]] = true;
        }
    }
    const auto minimize = get_ans();
    cout << maximize.size() << '\n';
    for (const auto& [x, y, z] : maximize) {
        cout << x << ' ' << y << ' ' << z << '\n';
    }
    cout << minimize.size() << '\n';
    for (const auto& [x, y, z] : minimize) {
        cout << x << ' ' << y << ' ' << z << '\n';
    }
}