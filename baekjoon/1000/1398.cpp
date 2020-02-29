#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        ll won; cin >> won;
        int ans = 0;
        while (won) {
            int tmp = won % 100; won /= 100;
            int cnt = INT_MAX, _25 = 0;
            while (tmp >= 0) {
                cnt = min(cnt, tmp / 10 + tmp % 10 + _25);
                tmp -= 25, ++_25;
            }
            ans += cnt;
        }
        cout << ans << '\n';
    }
    return 0;
}