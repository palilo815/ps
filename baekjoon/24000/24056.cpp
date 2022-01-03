#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    int m = n;
    while (m && a[m - 1] == b[m - 1]) --m;
    sort(a.begin(), a.begin() + m);
    while (m && a[m - 1] == b[m - 1]) --m;
    const auto [a_st, b_st] = ranges::mismatch(a, b);
    cout << (a_st == a.end() || (*a_st < *b_st && equal(b_st, b.begin() + m, next(a_st))));
}
