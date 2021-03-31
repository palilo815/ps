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

    vector<int> a(n + 1);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<int64_t> psum(n + 1);
    for (int i = 0; i < n; ++i)
        psum[i + 1] = psum[i] + a[i];

    int64_t ans = -1;
    int l = -1, r = -1;

    vector<int> stk;
    for (int i = 0; i < n + 1; ++i) {
        while (!stk.empty() && a[stk.back()] >= a[i]) {
            auto mn = a[stk.back()];
            stk.pop_back();

            auto sum = psum[i] - psum[stk.empty() ? 0 : stk.back() + 1];
            if (sum * mn > ans) {
                ans = sum * mn;
                l = stk.empty() ? 0 : stk.back() + 1;
                r = i - 1;
            }
        }
        stk.emplace_back(i);
    }
    cout << ans << '\n'
         << l + 1 << ' ' << r + 1;
}