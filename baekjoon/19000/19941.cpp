#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    string s;
    cin >> n >> k >> s;
    int ans = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (*it == 'P') {
            const auto target = find(max(s.begin(), it - k), min(s.end(), it + k + 1), 'H');
            if (target != min(s.end(), it + k + 1)) {
                *target = ' ';
                ++ans;
            }
        }
    }
    cout << ans;
}