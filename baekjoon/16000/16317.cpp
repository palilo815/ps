#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    array<bool, 366> pushed {};
    for (int i = n, d; i--;) {
        cin >> d;
        pushed[d] = true;
    }

    int cnt = 0, dirty = 0, ans = 0;
    for (const auto& d : pushed) {
        if (dirty + cnt >= 20) ++ans, dirty = cnt = 0;
        dirty += cnt;
        cnt += d;
    }
    cout << ans + (cnt || dirty);
}