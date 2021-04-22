#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t x;
    cin >> n >> x;

    if (x << 1 > int64_t(n - 1) * (n - 2))
        return cout << -1, 0;

    assert(n > 2);

    vector<bool> used(n - 1);
    cout << n << ' ';
    for (int64_t mn_h = 1; x > 0; ++mn_h) {
        mn_h = max(mn_h, n - 1 - x);
        cout << mn_h << ' ';
        x -= n - 1 - mn_h;
        used[mn_h] = true;
    }
    cout << n - 1;

    assert(x == 0);

    for (int i = n - 2; i; --i)
        if (!used[i])
            cout << ' ' << i;
}