#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> stk;
    int64_t ans = 0;
    for (int x; n--; stk.emplace_back(x)) {
        cin >> x;
        auto it = upper_bound(stk.rbegin(), stk.rend(), x);
        if (it != stk.rend()) ++it;

        ans += it - stk.rbegin();
        while (!stk.empty() && stk.back() < x)
            stk.pop_back();
    }
    cout << ans;
}