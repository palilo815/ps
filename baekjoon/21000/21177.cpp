#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int MX_N = 9e4;

    int n;
    cin >> n;

    vector<char> has(MX_N + 1);
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        has[x] = 1;
    }

    int ans = 0;
    for (int i = 1; i <= MX_N; ++i)
        if (has[i] && !has[i - 1])
            ans += i;
    cout << ans;
}