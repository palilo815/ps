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
    while (n && a[n - 1] == b[n - 1]) --n;
    sort(a.begin(), a.begin() + n);
    while (n && a[n - 1] == b[n - 1]) --n;
    const auto [a_st, b_st] = ranges::mismatch(a, b);
    cout << (a_st == a.end() || (*a_st < *b_st && equal(b_st, b.begin() + n, next(a_st))));
}
