#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, c, b;
    cin >> n >> c >> b;

    vector<bool> broken(n);
    for (int i; b--;) {
        cin >> i;
        broken[i - 1] = true;
    }

    vector<bool> ans(n);
    bool f = true;
    c & 1 ? ans[0] = true : f = false;

    for (int i = 1; i < n && c >= 2; ++i) {
        if (broken[i]) {
            f = false;
            continue;
        }

        if (i + 1 < n && !broken[i + 1]) {
            ans[i + f] = true;
            ++i, c -= 2;
        } else if (!f) {
            ans[i] = true;
            c -= 2;
        }
    }

    for (const auto& x : ans) cout << x;
}