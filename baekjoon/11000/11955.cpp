#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m, k;
    cin >> n >> m >> k;

    vector<string> mat(n);
    for (auto& x : mat) cin >> x;

    vector<vector<int>> psum(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            psum[i][j] = -psum[i - 1][j - 1] + psum[i - 1][j] + psum[i][j - 1] + (mat[i - 1][j - 1] == '*');

    int mx = -1, r = -1, c = -1;

    // 오른쪽 아래 코너 고정
    for (int i = k; i <= n; ++i)
        for (int j = k; j <= m; ++j)
            if (chmax(mx, psum[i - 1][j - 1] - psum[i - k + 1][j - 1] - psum[i - 1][j - k + 1] + psum[i - k + 1][j - k + 1]))
                r = i, c = j;

    assert(r != -1);

    mat[r - k][c - k] = mat[r - k][c - 1] = mat[r - 1][c - k] = mat[r - 1][c - 1] = '+';
    for (int i = c - k + 1; i < c - 1; ++i)
        mat[r - 1][i] = mat[r - k][i] = '-';
    for (int i = r - k + 1; i < r - 1; ++i)
        mat[i][c - 1] = mat[i][c - k] = '|';

    cout << mx << '\n';
    for (const auto& x : mat)
        cout << x << '\n';
}