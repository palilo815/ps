#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector earn(m, vector<int>(n + 1));
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        for (int j = 0; j < m; ++j) {
            cin >> earn[j][i];
        }
    }
    vector dp(m, vector<int>(n + 1, -1)), par(dp);
    dp[0] = earn[0];
    iota(par.front().begin(), par.front().end(), 0);
    for (int i = 1; i < m; ++i) {
        for (int use = 0; use <= n; ++use) {
            for (int j = 0; j + use <= n; ++j) {
                if (~dp[i - 1][j] && chmax(dp[i][j + use], dp[i - 1][j] + earn[i][use])) {
                    par[i][j + use] = use;
                }
            }
        }
    }
    int i = max_element(dp.back().begin(), dp.back().end()) - dp.back().begin();
    cout << dp.back()[i] << '\n';
    vector<int> recon(m);
    for (int j = m; j--;) {
        recon[j] = par[j][i];
        i -= par[j][i];
    }
    for (const auto& x : recon) {
        cout << x << ' ';
    }
}