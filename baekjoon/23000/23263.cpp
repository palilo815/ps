#include <bits/stdc++.h>

constexpr int MAX_N = 5e3;
constexpr int MAX_K = 1e6;
constexpr int INF = 0x3f3f3f3f;

std::array<int, MAX_N> b;
std::array<int, MAX_K + 1> dp;

auto run() {
    using namespace std;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    fill(dp.begin() + 1, dp.begin() + k + 1, INF);
    auto ans = INF;
    for (auto pivot = 0; pivot < n; ++pivot) {
        // [0..pivot) [pivot..n)
        for (auto i = pivot, acc = 0; i--;) {
            acc += b[i];
            if (acc > k) break;
            dp[acc] = min(dp[acc], pivot - i);
        }
        for (auto i = pivot, acc = 0; i < n;) {
            acc += b[i++];
            if (acc > k) break;
            ans = min(ans, dp[k - acc] + i - pivot);
        }
    }
    return ans != INF ? ans : -1;
}

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cout << "Case #" << tc << ": " << run() << '\n';
    }
}
