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

    vector<int> stk = {INT_MAX}; // sentinel
    int64_t ans = 0;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (x > stk.back()) {
            ans += x - stk.back();
            while (stk.back() < x) stk.pop_back();
        }
        if (x != stk.back()) stk.emplace_back(x);
    }

    if (stk.size() != 1) ans += stk[1] - stk.back();
    cout << ans;
}