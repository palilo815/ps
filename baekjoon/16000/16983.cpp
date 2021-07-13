#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    int64_t ans = 0;
    vector<array<int, 2>> coin(n);
    for (int x, y, i = 0; i < 2 * n; ++i) {
        cin >> x >> y;
        if (x < 1) {
            ans += 1 - x, x = 1;
        } else if (x > n) {
            ans += x - n, x = n;
        }
        if (y < 1) {
            ans += 1 - y, y = 1;
        } else if (y > 2) {
            ans += y - 2, y = 2;
        }
        ++coin[x - 1][y - 1];
    }
    array<int, 2> cnt {};
    for (int i = 0; i < n; ++i) {
        cnt[0] += coin[i][0] - 1, cnt[1] += coin[i][1] - 1;
        if (cnt[0] < 0 && cnt[1] > 0) {
            const int borrow = min(-cnt[0], cnt[1]);
            cnt[0] += borrow, cnt[1] -= borrow;
            ans += borrow;
        }
        if (cnt[1] < 0 && cnt[0] > 0) {
            const int borrow = min(-cnt[1], cnt[0]);
            cnt[1] += borrow, cnt[0] -= borrow;
            ans += borrow;
        }
        ans += abs(cnt[0]) + abs(cnt[1]);
    }
    cout << ans;
}