#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct quest_t {
    int x, t, y, r;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;
    int n, s1, s2;
    cin >> n >> s1 >> s2;
    vector<quest_t> quests(n);
    for (auto& [x, t, y, r] : quests) {
        cin >> x >> t >> y >> r;
    }
    sort(quests.begin(), quests.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.x < rhs.x;
    });
    vector dp(s1 + 1, vector(s2 + 1, INF));
    dp[0][0] = 0;
    for (const auto& [x, t, y, r] : quests) {
        for (int i = s1 + 1; i--;) {
            for (int j = s2 + 1; j--;) {
                if (dp[i][j] == INF) {
                    continue;
                }
                if (i != s1) {
                    int i2 = i + x, j2 = j;
                    if (i2 > s1) {
                        j2 = min(s2, j2 + i2 - s1);
                        i2 = s1;
                    }
                    chmin(dp[i2][j2], dp[i][j] + t);
                }
                if (j != s2) {
                    int j2 = min(s2, j + y);
                    chmin(dp[i][j2], dp[i][j] + r);
                }
            }
        }
    }
    cout << (dp[s1][s2] == INF ? -1 : dp[s1][s2]);
}