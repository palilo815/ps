#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector pref(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> pref[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            pref[i][j] += -pref[i - 1][j - 1] + pref[i - 1][j] + pref[i][j - 1];
        }
    }
    int ans = 0;
    for (int si = 0; si < n; ++si) {
        for (int sj = 0; sj < m; ++sj) {
            for (int ei = si + 1; ei <= n; ++ei) {
                bool flag = false;
                for (int ej = sj + 1; ej <= m; ++ej) {
                    const auto sum = pref[si][sj] - pref[si][ej] - pref[ei][sj] + pref[ei][ej];
                    if (sum == 10) ++ans;
                    if (sum >= 10) break;
                    flag = true;
                }
                if (!flag) break;
            }
        }
    }
    cout << ans;
}