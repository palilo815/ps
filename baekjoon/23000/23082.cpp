#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int64_t n;
    cin >> n;
    string ans;
    while (n) {
        auto r = n % 3;
        if (r < 0) r += 3;
        if (r == 1) {
            ans += '1';
            n = (n - 1) / 3;
        } else if (r == 0) {
            ans += '0';
            n /= 3;
        } else {
            ans += 'T';
            n = (n + 1) / 3;
        }
    }
    reverse(ans.begin(), ans.end());
    cout << (ans.empty() ? "0" : ans);
}