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

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    auto mx = *max_element(a.begin(), a.end());
    auto ans = accumulate(a.begin(), a.end(), 0LL) + mx;

    cout << (ans >> 1) << '.' << (ans & 1 ? 5 : 0);
}