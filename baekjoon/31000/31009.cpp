#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    array<int, 1002> cnt = {};
    int64_t ans = 0, cost;
    char s[16];
    while (n--) {
        cin >> s >> cost;
        if (strcmp(s, "jinju") == 0) {
            ans = cost;
        }
        ++cnt[min(1001L, cost)];
    }
    cout << ans << '\n';
    cout << accumulate(cnt.begin() + ans + 1, cnt.end(), 0);
}
