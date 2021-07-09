#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct tree {
    int x, y, r;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int INF = 0x3f3f3f3f;
    int n, m, w, h;
    cin >> n >> m >> w >> h;
    vector<tree> trees(n);
    for (auto& [x, y, r] : trees) {
        cin >> x >> y >> r;
    }
    vector dist(n + 4, vector<int>(n + 4));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dist[i][j] = dist[j][i] = (int(hypot(trees[i].x - trees[j].x, trees[i].y - trees[j].y) + 1e-6) - trees[i].r - trees[j].r) / 2;
        }
    }
    for (int i = 0; i < n; ++i) {
        dist[i][n + 0] = dist[n + 0][i] = (trees[i].y - trees[i].r) / 2;
        dist[i][n + 1] = dist[n + 1][i] = (trees[i].x - trees[i].r) / 2;
        dist[i][n + 2] = dist[n + 2][i] = (h - trees[i].y - trees[i].r) / 2;
        dist[i][n + 3] = dist[n + 3][i] = (w - trees[i].x - trees[i].r) / 2;
    }
    for (int i = n; i < n + 4; ++i) {
        for (int j = n; j < n + 4; ++j) {
            dist[i][j] = INF;
        }
    }
    /**
	 * [0, n) = trees
	 * n + a = sides
	 *  3----(2)----2
	 *  |           |
	 * (1)         (3)
	 *  |           |
	 *  0----(0)----1
	 */
    vector<bool> used(n + 4);
    vector<int> need(n + 4);
    auto solve = [&](int s) {
        fill(used.begin(), used.end(), false);
        fill(need.begin(), need.end(), INF);
        need[n + s] = 0;
        for (int _ = n + 4; _--;) {
            int k = -1;
            for (int i = 0; i < n + 4; ++i) {
                if (!used[i] && (k == -1 || need[i] < need[k])) {
                    k = i;
                }
            }
            assert(~k);
            used[k] = true;
            for (int i = 0; i < n + 4; ++i) {
                if (!used[i]) {
                    chmin(need[i], max(need[k], dist[k][i]));
                }
            }
        }
    };
    //  0 <-> 1 = 0 to others
    //  0 <-> 2 = (0,3) to (1,2)
    //  0 <-> 3 = 1 to others
    //  1 <-> 2 = 3 to others
    //  1 <-> 3 = (0,1) to (2,3)
    //  2 <-> 3 = 2 to others
    array<array<int, 4>, 4> res;
    for (int i = 0; i < 4; ++i) {
        solve(i);
        for (int j = 0; j < 4; ++j) {
            res[i][j] = i == j ? INF : need[n + j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            assert(res[i][j] == res[j][i]);
        }
    }
    array<array<int, 4>, 4> ans;
    ans[0][0] = ans[1][1] = ans[2][2] = ans[3][3] = INF;
    ans[0][1] = ans[1][0] = min({res[0][1], res[0][2], res[0][3]});
    ans[0][2] = ans[2][0] = min({res[0][1], res[0][2], res[3][1], res[3][2]});
    ans[0][3] = ans[3][0] = min({res[1][0], res[1][2], res[1][3]});
    ans[1][2] = ans[2][1] = min({res[3][0], res[3][1], res[3][2]});
    ans[1][3] = ans[3][1] = min({res[0][2], res[0][3], res[1][2], res[1][3]});
    ans[2][3] = ans[3][2] = min({res[2][0], res[2][1], res[2][3]});
    for (int r, c; m--;) {
        cin >> r >> c, --c;
        for (int i = 0; i < 4; ++i) {
            if (r <= ans[c][i]) {
                cout << i + 1;
            }
        }
        cout << '\n';
    }
}