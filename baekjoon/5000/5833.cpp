#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> friends(n);
    for (int x; auto& mask : friends) {
        cin >> x, mask |= 1 << (x - 1);
        cin >> x, mask |= 1 << (x - 1);
        cin >> x, mask |= 1 << (x - 1);
    }
    constexpr int INF {0x3f3f3f3f};
    vector dp(1 << n, INF);
    dp[0] = 0;
    for (auto sub {1}; sub < 1 << n; ++sub) {
        int outward {};
        for (int i {}; i < n; ++i) {
            if (sub >> i & 1) {
                outward += __builtin_popcount(~sub & friends[i]);
            }
        }
        for (int i {}; i < n; ++i) {
            const auto inward_of_i {__builtin_popcount(sub & friends[i])};
            if (sub >> i & 1) {
                dp[sub] = min(dp[sub], dp[sub ^ (1 << i)] + outward - 3 + (inward_of_i << 1));
            }
        }
    }
    cout << dp.back();
}
